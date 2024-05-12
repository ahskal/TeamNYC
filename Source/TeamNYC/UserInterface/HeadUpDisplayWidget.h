// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ExtendedUserWidget.h"
#include "HeadUpDisplayWidget.generated.h"

class UVerticalBox;
class USkillHotKeyWidget;

/**
 * 
 */
UCLASS()
class TEAMNYC_API UHeadUpDisplayWidget : public UExtendedUserWidget
{
	GENERATED_BODY()
	
public:
	UHeadUpDisplayWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	//====================================================================================
	// MEMBER VARIABLES
	//====================================================================================
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey", meta = (BindWidget))
	TObjectPtr<UVerticalBox> HotkeyContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Hotkey")
	TArray<FKey> HotKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Hotkey")
	int32 KeysPerRow{ 6 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill Hotkey")
	TArray<TObjectPtr<USkillHotKeyWidget>> SlotWidgets;
};
