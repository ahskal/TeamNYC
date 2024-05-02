
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT()
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FCharacterStat() : 
		MaxHealthPoint(0.0f), 
		HealthPointRegenerationAmount(0.0f),
		MaxManaPoint(0.0f), 
		ManaPointRegenerationAmount(0.0f),
		Damage(0.0f), 
		Armor(0.0f),
		AttackRange(0.0f), 
		AttackSpeed(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float HealthPointRegenerationAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxManaPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float ManaPointRegenerationAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MovementSpeed;

	FCharacterStat operator+(const FCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}

	FCharacterStat operator+=(const FCharacterStat& Other)
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		float* ResultPtr = reinterpret_cast<float*>(this);
		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] += OtherPtr[i];
		}

		return *this;
	}

	FCharacterStat operator-(const FCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] - OtherPtr[i];
		}

		return Result;
	}

	FCharacterStat operator-=(const FCharacterStat& Other)
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		float* ResultPtr = reinterpret_cast<float*>(this);
		int32 StatNum = sizeof(FCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] -= OtherPtr[i];
		}

		return *this;
	}
};

