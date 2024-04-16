#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"
#include "UserInterface/Inventory/DragItemVisual.h"

#include "Item/ItemBase/ItemBase.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Util/ColorConstants.h"

#define BLUE FLinearColor(0.f, 0.2f, 1.f)
#define ORANGE FLinearColor(1.f, 0.15f, 0.f)
#define GOLD FLinearColor(0.97f, 0.8f, 0.f)
#define CYAN FLinearColor(0.f, 1.f, 1.f)
#define PURPLE FLinearColor(0.3f, 0.f, 1.f)

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ToolTipClass)
	{
		UInventoryTooltip* ToolTip = CreateWidget<UInventoryTooltip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;

		SetToolTip(ToolTip);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemReference)
	{
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Useless:
			ItemBorder->SetBrushColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
			break;
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			//ItemBorder->SetBrushColor(FLinearColor::White);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(UE::Geometry::LinearColors::DarkCyan3b());
			//ItemBorder->SetBrushColor(FLinearColor::Green);
			break;
		case EItemQuality::Rare:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.1f, 1.0f));
			break;
		case EItemQuality::Epic:
			ItemBorder->SetBrushColor(PURPLE);
			break;
		case EItemQuality::Unique:
			ItemBorder->SetBrushColor(CYAN);
			break;
		case EItemQuality::Masterpiece:
			ItemBorder->SetBrushColor(UE::Geometry::LinearColors::Red3b());
			break;
		case EItemQuality::Mythic:
			ItemBorder->SetBrushColor(GOLD);
			break;
		case EItemQuality::Legendary:
			//ItemBorder->SetBrushColor(UE::Geometry::LinearColors::DarkOrange3b());
			ItemBorder->SetBrushColor(ORANGE);
			break;
		default:
			ItemBorder->SetBrushColor(FLinearColor::Black);
		}

		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);

		if (ItemReference->ItemNumericData.bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	//TODO: sub menu on right click goes here

	return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragItemVisualClass)
	{
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
		DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity));

		ItemReference->ItemNumericData.bIsStackable ?
			DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity))
			: DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		//UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		//DragItemOperation->SourceItem = ItemReference;
		//DragItemOperation->SourceInventory = ItemReference->OwningInventory;
		//
		//DragItemOperation->DefaultDragVisual = DragVisual;
		//DragItemOperation->Pivot = EDragPivot::TopLeft;
		//
		//OutOperation = DragItemOperation;

	}
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
