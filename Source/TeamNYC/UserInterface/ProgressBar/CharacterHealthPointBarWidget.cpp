// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ProgressBar/CharacterHealthPointBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interfaces/CharacterInterface/CharacterWidgetInterface.h"

UCharacterHealthPointBarWidget::UCharacterHealthPointBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

// 이득우꺼
// 스탯컴포넌트 초기화 이후에 불림
void UCharacterHealthPointBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HealthBar")));
	ensure(HpProgressBar);

	ICharacterWidgetInterface* CharacterWidget = Cast<ICharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UCharacterHealthPointBarWidget::UpdateHpBar(float NewCurrnetHp)
{
	ensure(MaxHp > 0.0f);

	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrnetHp / MaxHp);
	}
}

void UCharacterHealthPointBarWidget::SetHpBarColor(FLinearColor NewColor)
{
	if (HpProgressBar)
	{
		HpProgressBar->SetFillColorAndOpacity(NewColor);
	}
}
