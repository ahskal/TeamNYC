#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

UENUM()
enum class ETargetType : uint8
{
	Self				UMETA(DisplayName = "Self Casting"),		// 자기 자신
	SelectedEnemy		UMETA(DisplayName = "Selected Enemy"),		// 적 선택
	SelectedAlly		UMETA(DisplayName = "Selected Ally"),		// 아군 선택
	SelectedArea		UMETA(DisplayName = "Selected Area"),		// 영역 선택
	AreaAroundSelf		UMETA(DisplayName = "Area Around Self"),	// 자신 주변
	Nontarget			UMETA(DisplayName = "Nontarget"),			// 논타겟
};

UENUM()
enum class EDamageType : uint8
{
	Pyhsical			UMETA(DisplayName = "Pyhsical"),			// 물리
	Fire				UMETA(DisplayName = "Fire"),				// 불
	Cold				UMETA(DisplayName = "Cold"),				// 냉기
	Lightning			UMETA(DisplayName = "Lightning"),			// 번개
};

USTRUCT()
struct FSkillElementInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	public:
	FSkillElementInfo() :
		Name(FText::FromString("Element Name")), 
		Icon(nullptr),
		Color(FLinearColor::White) {}

	UPROPERTY(EditAnywhere, Category = "Skill")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "Skill")
	FText Description;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TObjectPtr<UTexture2D> LockedIcon;

	UPROPERTY(EditAnywhere, Category = "Skill")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, Category = "Skill")
	ETargetType TargetType;

	UPROPERTY(EditAnywhere, Category = "Skill")
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, Category = "Skill")
	bool bCanBeUnlocked;

	UPROPERTY(EditAnywhere, Category = "Skill")
	bool bAcquired;
};
