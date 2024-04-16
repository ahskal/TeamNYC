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

	// �߰� ü��
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AdditionalHp;

	// ���ݷ�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Damage;

	// ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Armor;

	// ���� ��Ÿ�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackRange;

	// ���� ��Ÿ�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpeed;
	
	// �̵��ӵ�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MovementSpeed;

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

protected:
	virtual void NativeConstruct() override;
private:
	void SetTextBlockValue(UTextBlock* TextBlock, int32 Value,FText Text = FText::FromString(""));
	
};
