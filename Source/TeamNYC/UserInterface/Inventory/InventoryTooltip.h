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

	// ������ �̸�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	// ������ Ÿ��-> ���, ���� ���
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	// ���ݷ�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;

	// ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorValue;

	// ���� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	// ������ ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	// �ִ� ���� ������ �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSizeText;

	// �Ǹ� ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	// �ִ밪
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSizeValue;

	// ���簪
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
