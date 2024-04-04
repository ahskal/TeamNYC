// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UI/ExtendedWidgetComponent.h"
#include "Character/UI/ExtendedUserWidget.h"
#include "Components/ProgressBar.h"

void UExtendedWidgetComponent::InitWidget()
{
	Super::InitWidget();

	//UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetUserWidgetObject());
	UExtendedUserWidget* ExtendedUserWidget = Cast<UExtendedUserWidget>(GetWidget());
	if (ExtendedUserWidget)
	{
		ExtendedUserWidget->SetOwingActor(GetOwner());
	}
}
