// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ProgressBar/StatBar.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Character/Player/PlayerCharacter.h"

#include "Character/Interfaces/CharacterWidgetInterface.h"

UStatBar::UStatBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// 내꺼
// 스탯컴포넌트 초기화 이전에 불림
void UStatBar::NativeConstruct()
{
	Super::NativeConstruct();

	//StatBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP Bar")));
	StatBar->SetFillColorAndOpacity(BarColor);
	DynamicMaterialInstance = StatRemoveBar->GetDynamicMaterial();
	DynamicMaterialInstance->SetVectorParameterValue("Color", RemoveBarColor);


	OwningActor = Cast<AActor>(GetOwningPlayerPawn());
	//OwningActor = Cast<AActor>(GetOwningPlayer());
	//PlayerRef = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (OwningActor)
	{
		ICharacterWidgetInterface* CharacterWidget = Cast<ICharacterWidgetInterface>(OwningActor);
		if (CharacterWidget)
		{
			CharacterWidget->SetupCharacterWidget(this);
		}
	}
}

void UStatBar::SetCurrentValue(float NewCurrentValue)
{
	StatData.CurrentValue = FMath::Clamp<float>(NewCurrentValue, StatData.MinValue, StatData.MaxValue);

	UpdateProgressBar();
}

void UStatBar::SetMaxValue(float NewMaxHp)
{
	StatData.MaxValue = NewMaxHp;

	UpdateProgressBar();
}

void UStatBar::UpdateProgressBar()
{
	if (StatData.MaxValue <= 0.0f)
	{
		return;
	}

	if (StatBar)
	{
		float Percent = FMath::Clamp(StatData.CurrentValue / StatData.MaxValue, 0.0f, 1.0f);
		StatBar->SetPercent(Percent);
		UpdateTextBlock();
	}
}

void UStatBar::UpdateTextBlock()
{
	if (StatText)
	{
		// float to int
		int32 CurrentValue = FMath::FloorToInt(StatData.CurrentValue);
		int32 MaxValue = FMath::FloorToInt(StatData.MaxValue);


		StatText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentValue, MaxValue)));
	}
}
