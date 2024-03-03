// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Interaction/InteractionWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.f;
}

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InteractionProgressBar->PercentDelegate.BindUFunction(
		this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KeyPressText->SetText(FText::FromString("Use"));
	CurrentInteractionDuration = 0.f;
}

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	switch (InteractableData->InteractableType)
	{
	case EInteractableType::Pickup:
		//	ActionText->SetText(FText::FromString("examine"));

		KeyPressText->SetText(FText::FromString("Press"));

		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		if (InteractableData->Quantity == 1)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(
				FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"),
					InteractableData->Quantity)
			);
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	default:
		break;
	}
	//	ActionText->SetText(InteractableData->Action);
	NameText->SetText(InteractableData->Name);
}
