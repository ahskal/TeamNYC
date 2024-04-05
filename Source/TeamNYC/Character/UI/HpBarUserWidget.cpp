// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UI/HpBarUserWidget.h"
#include "Components/ProgressBar.h"
#include "Character/Interfaces/CharacterWidgetInterface.h"

UHpBarUserWidget::UHpBarUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UHpBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	ensure(HpProgressBar);

	ICharacterWidgetInterface* CharacterWidget = Cast<ICharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UHpBarUserWidget::UpdateHpBar(float NewCurrnetHp)
{
	ensure(MaxHp > 0.0f);

	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrnetHp / MaxHp);
	}
}

void UHpBarUserWidget::SetHpBarColor(FLinearColor NewColor)
{
	if (HpProgressBar)
	{
		HpProgressBar->SetFillColorAndOpacity(NewColor);
	}
}
