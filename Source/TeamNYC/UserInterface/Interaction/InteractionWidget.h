#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FInteractableData;
class APlayerCharacter;
class UProgressBar;
class UTextBlock;

UCLASS()
class TEAMNYC_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	//====================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	UTextBlock* NameText;
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	UTextBlock* ActionText;
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	UTextBlock* QuantityText;
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	UTextBlock* KeyPressText;
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	UProgressBar* InteractionProgressBar;
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data", meta = (BindWidget))
	float CurrentInteractionDuration;

	//====================================================================================
	// FUNCTIONS
	//====================================================================================
	UFUNCTION(Category = "Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	//====================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	APlayerCharacter* PlayerReference;

	//====================================================================================
	// FUNCTIONS
	//====================================================================================

	void UpdateWidget(const FInteractableData* InteractableData) const;
};
