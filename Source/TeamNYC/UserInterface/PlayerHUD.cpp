// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerHUD.h"

#include "Character/Player/PlayerCharacter.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "UserInterface/MainMenu.h"


APlayerHUD::APlayerHUD()
{
	FString MainWidgetPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UserInterface/ProgressBar/W_Main.W_Main_C'");
	ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetClassRef(*MainWidgetPath);
	if (MainWidgetClassRef.Succeeded())
	{
		MainWidgetClass = MainWidgetClassRef.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("HUD BeginPlay executing"));

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//if (MainWidgetClass)
	//{
		MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport(1);
		MainWidget->SetVisibility(ESlateVisibility::Visible);
	//}
}


void APlayerHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();

		//const FInputModeGameOnly InputMode;
		//GetOwningPlayerController()->SetInputMode(InputMode);
		//GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();

		//const FInputModeGameAndUI InputMode;
		//GetOwningPlayerController()->SetInputMode(InputMode);
		//GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void APlayerHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}
