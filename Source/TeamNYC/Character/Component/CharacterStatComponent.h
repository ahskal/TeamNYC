// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/CharacterStat.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMNYC_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();

protected:
	virtual void BeginPlay() override;

	//====================================================================================
	//  HP Section
	//====================================================================================
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentHp;

public:
	FOnHPIsZeroDelegate OnHpIsZero;
	FOnHPChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxHp() const { return TotalStat.MaxHp; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetHpRatio() const { return CurrentHp / GetMaxHp(); }
	void SetHp(float NewHp);
	
	float ApplyDamage(float InDamage);

	//====================================================================================
	//  Stat Section
	//====================================================================================
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FCharacterStat ModifierStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FCharacterStat TotalStat;

public:
	FORCEINLINE FCharacterStat& GetTotalStat() { return TotalStat; }
	FORCEINLINE void SetTotalStat() { TotalStat = BaseStat + ModifierStat; }
	FORCEINLINE void AddModifierStat(const FCharacterStat& InModifierStat) { ModifierStat += InModifierStat; }
};
