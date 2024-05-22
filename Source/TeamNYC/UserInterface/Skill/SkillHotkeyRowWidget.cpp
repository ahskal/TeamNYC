// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/SkillHotkeyRowWidget.h"
#include "UserInterface/Skill/SkillHotKeyWidget.h"
#include "Components/HorizontalBox.h"

USkillHotkeyRowWidget::USkillHotkeyRowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void USkillHotkeyRowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HotKeys.Add("1");
	HotKeys.Add("2");
	HotKeys.Add("3");
	HotKeys.Add("4");
	HotKeys.Add("5");
	HotKeys.Add("6");

	//HotKeys.Add("Q");
	//HotKeys.Add("W");
	//HotKeys.Add("E");
	//HotKeys.Add("R");
	//HotKeys.Add("T");
	//HotKeys.Add("Y");
}

TArray<TObjectPtr<USkillHotKeyWidget>> USkillHotkeyRowWidget::GenerateHotkeyRow()
{
	for (auto& Hotkey : HotKeys)
	{
		USkillHotKeyWidget* HotkeyWidget = CreateWidget<USkillHotKeyWidget>(this, USkillHotKeyWidget::StaticClass());
		SlotWidgets.Add(HotkeyWidget);
		Box->AddChildToHorizontalBox(HotkeyWidget);
	}

	return SlotWidgets;
}
