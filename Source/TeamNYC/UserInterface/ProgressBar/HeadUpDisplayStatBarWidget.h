// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ExtendedUserWidget.h"
#include "Data/StatProgressBarData.h"
#include "HeadUpDisplayStatBarWidget.generated.h"


class USizeBox;
class UOverlay;
class UProgressBar;
class UTextBlock;
class UImage;
class APlayerCharacter;
struct FStatData;

/**
 *
 */
UCLASS()
class TEAMNYC_API UHeadUpDisplayStatBarWidget : public UExtendedUserWidget
{
	GENERATED_BODY()

public:
	UHeadUpDisplayStatBarWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;
	
	//====================================================================================
	// MEMBER VARIABLES
	//====================================================================================
public:
	// progress bar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat Bar", meta = (BindWidget))
	TObjectPtr<UProgressBar> StatBar;

	// image
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat Bar", meta = (BindWidget))
	TObjectPtr<UImage> StatRemoveBar;

	// text
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat Bar", meta = (BindWidget))
	TObjectPtr<UTextBlock> StatText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor BarColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor RemoveBarColor;

	// material instance dynamic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material")
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	//====================================================================================
	// Stat Data
	//====================================================================================
protected:
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	EStatProgressBarType	StatType;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	FStatData				StatData;

public:
	FORCEINLINE EStatProgressBarType GetStatType() const { return StatType; }
	FORCEINLINE FStatData GetStatData() const { return StatData; }
	FORCEINLINE void SetStatType(EStatProgressBarType NewStatType) { StatType = NewStatType; }
	FORCEINLINE void SetStatData(FStatData& NewStatData) { StatData = NewStatData; }

	//====================================================================================
	// FUNCTIONS
	//====================================================================================
public:
	void SetCurrentValue(float NewCurrentValue);
	void SetMaxValue(float NewMaxHp);
	void UpdateProgressBar();
	void UpdateTextBlock();

	//====================================================================================
	// FUNCTIONS
	//====================================================================================
};

