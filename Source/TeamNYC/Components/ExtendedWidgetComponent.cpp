// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ExtendedWidgetComponent.h"
#include "UserInterface/ExtendedUserWidget.h"
#include "Components/ProgressBar.h"

void UExtendedWidgetComponent::InitWidget()
{
	Super::InitWidget();

	//UExtendedUserWidget* ExtendedUserWidget = Cast<UExtendedUserWidget>(GetUserWidgetObject());
	UExtendedUserWidget* ExtendedUserWidget = Cast<UExtendedUserWidget>(GetWidget());
	if (ExtendedUserWidget)
	{
		ExtendedUserWidget->SetOwningActor(GetOwner());
	}
}
