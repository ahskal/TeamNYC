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

	// 툴팁 테두리
	UPROPERTY(meta = (BindWidget))
	UBorder* ItemBorder;

	// 아이템 이름
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	// 아이템 타입-> 장비, 포션 등등
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	// 추가스텟 툴팁 박스
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

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

	// 판매 가격
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	// 무게
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeightValue;

protected:
	virtual void NativeConstruct() override;
private:
	// 가변 인수 템플릿
	template<typename... Args>
	void SetTextBlockTextToText(UTextBlock* TextBlock, Args...args);
};

