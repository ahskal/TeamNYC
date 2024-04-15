// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/CharacterStatComponent.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	BaseStat.MaxHp = 10.0f;
	BaseStat.Damage = 1.0f;
	BaseStat.AttackSpeed = 1.0f;
	BaseStat.AttackRange = 40.0f;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetTotalStat();
	SetHp(TotalStat.MaxHp);
}


float UCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, CurrentHp);

	SetHp(PrevHp - ActualDamage);

	return ActualDamage;
}

void UCharacterStatComponent::SetHp(float NewHp)
{
	// Set new HP
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, GetMaxHp());

	// Broadcast OnHpChanged
	OnHpChanged.Broadcast(CurrentHp);

	// Check if HP is zero
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpIsZero.Broadcast();
	}
}

