// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UMainMenu;
class UInventoryPanel;
class UInteractionWidget;
struct FInteractableData;

UCLASS()
class TEAMNYC_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryPanel> InventoryPanelClass;

	bool bIsMenuVisible;

protected:
	virtual void BeginPlay() override;

public:
	APlayerHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;
};
