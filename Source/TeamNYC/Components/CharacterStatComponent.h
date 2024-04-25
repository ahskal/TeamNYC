// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/CharacterStat.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHealthPointIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthPointChangedDelegate,	float /*Current HP*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnManaPointChangedDelegate,	float /*Current MP*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnExperiencePointChangedDelegate,	float /*Current EXP*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMNYC_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;


	//====================================================================================
	//  HealthPoint Section
	//====================================================================================
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentHealthPoint;

public:
	FOnHealthPointIsZeroDelegate	OnHealthPointIsZero;
	FOnHealthPointChangedDelegate	OnHealthPointChanged; 
	

	FORCEINLINE float GetMaxHealthPoint() const		{ return TotalStat.MaxHealthPoint; }
	FORCEINLINE float GetCurrentHealthPoint() const { return CurrentHealthPoint;}
	FORCEINLINE float GetHealthPointRatio() const	{ return CurrentHealthPoint / GetMaxHealthPoint(); }
	void SetCurrentHealthPoint(float NewHealthPoint);
	
	float ApplyDamage(float InDamage);
	float Heal(float InHealAmount);



	//====================================================================================
	//  ManaPoint Section
	//====================================================================================
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentManaPoint;

public:
	FOnManaPointChangedDelegate		OnManaPointChanged;

	FORCEINLINE float GetMaxManaPoint() const		{ return TotalStat.MaxManaPoint; }
	FORCEINLINE float GetCurrentManaPoint() const	{ return CurrentManaPoint; }
	FORCEINLINE float GetManaPointRatio() const		{ return CurrentManaPoint / GetMaxManaPoint(); }
	void SetCurrentManaPoint(float NewManaPoint);

	float ApplyManaCost(float InManaCost);
	float RestoreMana(float InManaAmount);


	//====================================================================================
	//  Regeneration Section
	//====================================================================================
protected:
	FTimerHandle	RegenerationTimerHandle;
	float			RegenerationInterval{ 5.0f };

public:
	void StartRegeneration();
	//void StopRegeneration();
	void HealthAndManaRegeneration();


	//====================================================================================
	//  Experience Section
	//====================================================================================
protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float MaxExperiencePoint;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentExperiencePoint;

public:
	FOnExperiencePointChangedDelegate	OnExperiencePointChanged;

	FORCEINLINE float GetMaxExperiencePoint() const		{ return MaxExperiencePoint; }
	FORCEINLINE float GetCurrentExperiencePoint() const	{ return CurrentExperiencePoint; }
	FORCEINLINE float GetExperiencePointRatio() const	{ return CurrentExperiencePoint / MaxExperiencePoint; }
	void SetCurrentExperiencePoint(float NewExperiencePoint);


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
