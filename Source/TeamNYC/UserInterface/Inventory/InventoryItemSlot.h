// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

class UTextBlock;
class UImage;
class UBorder;
class UInventoryTooltip;
class UDragItemVisual;
class UItemBase;

UCLASS()
class TEAMNYC_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
public:

	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; }
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UDragItemVisual> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UInventoryTooltip> ToolTipClass;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UTextBlock* ItemQuantity;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	// FPointerEvent는 마우스의 이벤트를 감지하는 타입
	// 마우스가 누르거나 올라가있거나 하는 이벤트를 받아오는 값

	// 마우스로 눌렀을때
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 마우스가 범위에서 떠났을때
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	// 마우스로 드래그를 할때
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	// 마우스가 해당 객체를 놨을때
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
