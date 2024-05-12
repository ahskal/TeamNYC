// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillHotKeyWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TEAMNYC_API USkillHotKeyWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	USkillHotKeyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	//====================================================================================
	// MEMBER VARIABLES
	//====================================================================================
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UImage> Background;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UImage> SkillIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UImage> CooldownImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UTextBlock> HotkeyText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UButton> SkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Hotkey")
	FKey HotKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material")
	TObjectPtr<UMaterialInstanceDynamic> CooldownDynamicMaterial;
};
