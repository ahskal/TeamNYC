// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatBar.generated.h"

class USizeBox;
class UOverlay;
class UProgressBar;
class UTextBlock;
class UImage;

/**
 *
 */
UCLASS()
class TEAMNYC_API UStatBar : public UUserWidget
{
	GENERATED_BODY()

	public:
	
	// size box
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat Bar", meta = (BindWidget))
	//TObjectPtr<USizeBox> SizeBox;

	// overlay
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat Bar", meta = (BindWidget))
	//TObjectPtr<UOverlay> Overlay;

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

protected:
	virtual void NativeConstruct() override;
};
