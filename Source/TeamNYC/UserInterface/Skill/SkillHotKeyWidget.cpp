// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/SkillHotKeyWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


USkillHotKeyWidget::USkillHotKeyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void USkillHotKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FString HotkeyName = FString::Printf(TEXT("[%s]"), *HotKey.GetDisplayName().ToString());
	HotkeyText->SetText(FText::FromString(HotkeyName));

	CooldownDynamicMaterial = CooldownImage->GetDynamicMaterial();
}
