// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	MaxExperiencePoint = 100.0f;

	BaseStat.MaxHealthPoint = 10.0f;
	BaseStat.MaxManaPoint = 10.0f;
	BaseStat.Damage = 1.0f;
	BaseStat.AttackSpeed = 1.0f;
	BaseStat.AttackRange = 40.0f;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	//SetTotalStat();
	//SetCurrentHealthPoint(TotalStat.MaxHealthPoint);
	//SetCurrentManaPoint(TotalStat.MaxManaPoint);
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

void UCharacterStatComponent::SetCurrentExperiencePoint(float NewExperiencePoint)
{
	// Set new EXP
	CurrentExperiencePoint = FMath::Clamp<float>(NewExperiencePoint, 0.0f, MaxExperiencePoint);

	// Broadcast OnExperiencePointChanged
	OnExperiencePointChanged.Broadcast(CurrentExperiencePoint);
}
