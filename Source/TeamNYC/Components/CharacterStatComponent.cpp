// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	MaxExperiencePoint = 100.0f;

	BaseStat.MaxHealthPoint = 100.0f;
	BaseStat.HealthPointRegenerationAmount = 5.0f;
	BaseStat.MaxManaPoint = 100.0f;
	BaseStat.ManaPointRegenerationAmount = 4.0f;
	BaseStat.Damage = 7.0f;
	BaseStat.AttackSpeed = 1.0f;
	BaseStat.AttackRange = 40.0f;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRegeneration();
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetTotalStat();
	SetCurrentHealthPoint(TotalStat.MaxHealthPoint);
	SetCurrentManaPoint(TotalStat.MaxManaPoint);
	SetCurrentExperiencePoint(0.0f);
}

float UCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHealthPoint = CurrentHealthPoint;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, CurrentHealthPoint);

	SetCurrentHealthPoint(PrevHealthPoint - ActualDamage);

	return ActualDamage;
}

float UCharacterStatComponent::Heal(float InHealAmount)
{
	const float PrevHealthPoint = CurrentHealthPoint;
	const float ActualHealAmount = FMath::Clamp<float>(InHealAmount, 0.0f, GetMaxHealthPoint() - CurrentHealthPoint);

	SetCurrentHealthPoint(PrevHealthPoint + ActualHealAmount);

	return ActualHealAmount;
}

void UCharacterStatComponent::StartRegeneration()
{
	if (RegenerationTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenerationTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(RegenerationTimerHandle, this, &UCharacterStatComponent::HealthAndManaRegeneration, RegenerationInterval, true, 1.0f);
}

void UCharacterStatComponent::HealthAndManaRegeneration()
{
	Heal(TotalStat.HealthPointRegenerationAmount);	
	RestoreMana(TotalStat.ManaPointRegenerationAmount);
}


void UCharacterStatComponent::SetCurrentHealthPoint(float NewHealthPoint)
{
	// Set new HP
	CurrentHealthPoint = FMath::Clamp<float>(NewHealthPoint, 0.0f, GetMaxHealthPoint());

	// Broadcast OnHealthPointChanged
	OnHealthPointChanged.Broadcast(CurrentHealthPoint);

	// Check if HealthPoint is zero
	if (CurrentHealthPoint <= KINDA_SMALL_NUMBER)
	{
		OnHealthPointIsZero.Broadcast();
	}
}

void UCharacterStatComponent::SetCurrentManaPoint(float NewManaPoint)
{
	// Set new MP
	CurrentManaPoint = FMath::Clamp<float>(NewManaPoint, 0.0f, GetMaxManaPoint());

	// Broadcast OnHealthPointChanged
	OnManaPointChanged.Broadcast(CurrentManaPoint);
}

float UCharacterStatComponent::ApplyManaCost(float InManaCost)
{
	const float PrevManaPoint = CurrentManaPoint;
	const float ActualManaCost = FMath::Clamp<float>(InManaCost, 0.0f, CurrentManaPoint);

	SetCurrentManaPoint(PrevManaPoint - ActualManaCost);

	return ActualManaCost;
}

float UCharacterStatComponent::RestoreMana(float InManaAmount)
{
	const float PrevManaPoint = CurrentManaPoint;
	const float ActualManaAmount = FMath::Clamp<float>(InManaAmount, 0.0f, GetMaxManaPoint() - CurrentManaPoint);

	SetCurrentManaPoint(PrevManaPoint + ActualManaAmount);

	return ActualManaAmount;
}

void UCharacterStatComponent::SetCurrentExperiencePoint(float NewExperiencePoint)
{
	// Set new EXP
	CurrentExperiencePoint = FMath::Clamp<float>(NewExperiencePoint, 0.0f, MaxExperiencePoint);

	// Broadcast OnExperiencePointChanged
	OnExperiencePointChanged.Broadcast(CurrentExperiencePoint);
}

void UCharacterStatComponent::ModifyDamage(float value)
{
	ModifierStat.Damage += value;
	SetTotalStat();
}
