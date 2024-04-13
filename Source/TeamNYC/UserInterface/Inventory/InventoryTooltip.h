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

	// 아이템 이름
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	// 아이템 타입-> 장비, 포션 등등
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	// 공격력
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;

	// 방어력
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorValue;

	// 사용법 설명 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	// 아이템 설명
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	// 최대 스택 사이즈 텍스트
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSizeText;

	// 판매 가격
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	// 최대값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSizeValue;

	// 현재값
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeightValue;

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
	//UTextBlock* StackWeightValue;
protected:
	virtual void NativeConstruct() override;
};
