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
		DisplayedValue(0.0f) {}
	
	UPROPERTY(EditAnywhere, Category = Stat)
	float MinValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float MaxValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float CurrentValue;

	UPROPERTY(EditAnywhere, Category = Stat)
	float DisplayedValue;
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