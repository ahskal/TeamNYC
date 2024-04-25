// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ProgressBar/HeadUpDisplayStatBarWidget.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/TimelineComponent.h"
#include "Character/Player/PlayerCharacter.h"

#include "Interfaces/CharacterInterface/CharacterWidgetInterface.h"

#include <Kismet/KismetMathLibrary.h>


UHeadUpDisplayStatBarWidget::UHeadUpDisplayStatBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UHeadUpDisplayStatBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StatBar->SetFillColorAndOpacity(BarColor);
	DynamicMaterialInstance = StatRemoveBar->GetDynamicMaterial();
	DynamicMaterialInstance->SetVectorParameterValue("Color", RemoveBarColor);


	OwningActor = Cast<AActor>(GetOwningPlayerPawn());
	if (OwningActor)
	{
		ICharacterWidgetInterface* CharacterWidget = Cast<ICharacterWidgetInterface>(OwningActor);
		if (CharacterWidget)
		{
			CharacterWidget->SetupCharacterWidget(this);
			UpdateProgressBar();
		}
	}

	//====================================================================================
	// Timeline Initialize
	//====================================================================================
	TimelineEventUpdateFunc.BindUFunction(this, "ProgressBarLerpUpdate");
	TimelineEventFinishedFunc.BindUFunction(this, "ProgressBarLerpFinish");

	Timeline.SetTimelinePostUpdateFunc(TimelineEventUpdateFunc);
	Timeline.SetTimelineFinishedFunc(TimelineEventFinishedFunc);
	Timeline.SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
}

void UHeadUpDisplayStatBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Timeline.TickTimeline(InDeltaTime);
}

void UHeadUpDisplayStatBarWidget::SetCurrentValue(float NewCurrentValue)
{
	StatData.DisplayedValue = StatData.CurrentValue;
	StatData.CurrentValue = FMath::Clamp<float>(NewCurrentValue, StatData.MinValue, StatData.MaxValue);

	ProgressBarLerpStart();
}

void UHeadUpDisplayStatBarWidget::SetMaxValue(float NewMaxHp)
{
	StatData.MaxValue = NewMaxHp;

	UpdateProgressBar();
}

void UHeadUpDisplayStatBarWidget::UpdateProgressBar()
{
	if (StatData.MaxValue <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	if (StatBar)
	{

		// Set Percent
		float DisplayedPercent = FMath::Clamp(StatData.DisplayedValue / StatData.MaxValue, 0.0f, 1.0f);
		StatBar->SetPercent(DisplayedPercent);

		// Set Color
		FLinearColor CurrentColor = UKismetMathLibrary::LinearColorLerpUsingHSV(RemoveBarColor, BarColor, DisplayedPercent);
		StatBar->SetFillColorAndOpacity(CurrentColor);

		// Set Text
		UpdateTextBlock();
	}
}

void UHeadUpDisplayStatBarWidget::UpdateTextBlock()
{
	if (StatText)
	{
		int32 DisplayedValue = FMath::FloorToInt(StatData.DisplayedValue);
		int32 MaxValue = FMath::FloorToInt(StatData.MaxValue);

		StatText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), DisplayedValue, MaxValue)));
	}
}

void UHeadUpDisplayStatBarWidget::ProgressBarLerpStart()
{
	LerpData.OriginalValue = StatData.DisplayedValue;
	LerpData.ValueToLerpTo = StatData.CurrentValue;
	LerpData.bIsPositive = StatData.CurrentValue > StatData.DisplayedValue;

	FName ParameterName = (LerpData.bIsPositive ? TEXT("PercentRight") : TEXT("PercentLeft"));
	float ValueRatio = StatData.CurrentValue / StatData.MaxValue;
	DynamicMaterialInstance->SetScalarParameterValue(ParameterName, ValueRatio);

	StatRemoveBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Timeline.SetTimelineLength(LerpTime);
	Timeline.PlayFromStart();
}

void UHeadUpDisplayStatBarWidget::ProgressBarLerpUpdate()
{

	float PlaybackPosition = Timeline.GetPlaybackPosition();
	float TimelineLength = Timeline.GetTimelineLength();
	float PlaybackRate = PlaybackPosition / TimelineLength;
	StatData.DisplayedValue = UKismetMathLibrary::Lerp(LerpData.OriginalValue, LerpData.ValueToLerpTo, PlaybackRate);

	FName ParameterName = (LerpData.bIsPositive ? TEXT("PercentLeft") : TEXT("PercentRight"));
	float ValueRatio = StatData.DisplayedValue / StatData.MaxValue;
	DynamicMaterialInstance->SetScalarParameterValue(ParameterName, ValueRatio);

	UpdateProgressBar();
}

void UHeadUpDisplayStatBarWidget::ProgressBarLerpFinish()
{
	StatData.DisplayedValue = StatData.CurrentValue;

	StatRemoveBar->SetVisibility(ESlateVisibility::Hidden);
}
