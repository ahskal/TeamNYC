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

	// 추가 체력
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AdditionalHp;

	// 공격력
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Damage;

	// 방어력
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Armor;

	// 공격 사거리
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackRange;

	// 공격 사거리
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpeed;
	
	// 이동속도
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MovementSpeed;

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

protected:
	virtual void NativeConstruct() override;
private:
	void SetTextBlockValue(UTextBlock* TextBlock, int32 Value,FText Text = FText::FromString(""));
	
};
