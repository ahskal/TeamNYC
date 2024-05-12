// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillHotkeyRowWidget.generated.h"

class UHorizontalBox;
class USkillHotKeyWidget;

/**
 * 
 */
UCLASS()
class TEAMNYC_API USkillHotkeyRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USkillHotkeyRowWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	//====================================================================================
	// MEMBER VARIABLES
	//====================================================================================
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UHorizontalBox> Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (ExposeOnSpawn = true))
	TArray<FKey> HotKeys;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey")
	TArray<TObjectPtr<USkillHotKeyWidget>> SlotWidgets;

public:
	TArray<TObjectPtr<USkillHotKeyWidget>> GenerateHotkeyRow();
};
