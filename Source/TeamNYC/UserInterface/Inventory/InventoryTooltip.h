#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlot;
class UTextBlock;

UCLASS()
class TEAMNYC_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	UInventoryItemSlot* InventorySlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorRating;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSize;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSizeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeight;

	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* QuestText;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* QualityText;
	//UPROPERTY()
	//UTextBlock* DamageLabel;
	//UPROPERTY()
	//UTextBlock* ArmorLabel;
	//UPROPERTY()
	//UTextBlock* StackSizeLabel;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* StackSizeText;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* SellValue;
	//UPROPERTY(meta = (BindWidget))
	//UTextBlock* StackWeightValue;
protected:
	virtual void NativeConstruct() override;
};
