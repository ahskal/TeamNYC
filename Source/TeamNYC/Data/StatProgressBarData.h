#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StatProgressBarData.generated.h"

UENUM()
enum class EStatProgressBarType : uint8
{
	Null, Health, Mana, Experience
};

USTRUCT()
struct FStatData
{
	GENERATED_BODY()
	
	public:
	FStatData() : 
		MinValue(0), 
		MaxValue(0), 
		CurrentValue(0), 
		DisplayedValue(0.0f), 
		MinLerpTime(0.2f), 
		MaxLerpTime(1.5f), 
		BarWidget(nullptr), 
		bIsCurrentlyAnimated(false), 
		bHasRegeneration(false), 
		TimeToRegMaxValue(45.0f),
		RegInterval(0.4f),
		//RegenerationTimer(nullptr),
		RegFuntionName(TEXT("")) {}
	
	UPROPERTY(EditAnywhere, Category = Stat)
	float MinValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float MaxValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float CurrentValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float DisplayedValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float MinLerpTime;

	UPROPERTY(EditAnywhere, Category = Stat)
	float MaxLerpTime;

	UPROPERTY(EditAnywhere, Category = Stat)
	TObjectPtr<class UHeadUpDisplayStatBarWidget> BarWidget;

	UPROPERTY(EditAnywhere, Category = Stat)
	bool bIsCurrentlyAnimated;

	UPROPERTY(EditAnywhere, Category = Stat)
	bool bHasRegeneration;

	UPROPERTY(EditAnywhere, Category = Stat)
	float TimeToRegMaxValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float RegInterval;

	//UPROPERTY(EditAnywhere, Category = Stat)
	//TObjectPtr<class FTimerHandle> RegenerationTimer;

	UPROPERTY(EditAnywhere, Category = Stat)
	FString RegFuntionName;
};

USTRUCT()
struct FStatLerp
{
	GENERATED_BODY()

	public:
	FStatLerp() :
		OriginalValue(0.0f),
		ValueToLerpTo(0.0f),
		bIsPositive(false) {}

	UPROPERTY(EditAnywhere, Category = Stat)
	float OriginalValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float ValueToLerpTo;

	UPROPERTY(EditAnywhere, Category = Stat)
	bool bIsPositive;
};