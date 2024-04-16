#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlot;
class UBorder;
class UTextBlock;
class UVerticalBox;

UCLASS()
class TEAMNYC_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	UInventoryItemSlot* InventorySlotBeingHovered;

	// ���� �׵θ�
	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBorder;

	// ������ �̸�
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	// ������ Ÿ��-> ���, ���� ���
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	// �߰����� ���� �ڽ�
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

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

	// �Ǹ� ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	// ����
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeightValue;

protected:
	virtual void NativeConstruct() override;
private:
	// ���� �μ� ���ø�
	template<typename... Args>
	void SetTextBlockTextToText(UTextBlock* TextBlock, Args...args);
};

