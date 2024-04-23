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

	// 아이템이 있는지 판단 여부
	if (ItemReference)
	{
		// 아이템 등급
		switch (ItemReference->ItemQuality)
		{
		case EItemQuality::Useless:
			ItemBorder->SetBrushColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
			break;
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(UE::Geometry::LinearColors::DarkCyan3b());
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
			ItemBorder->SetBrushColor(ORANGE);
			break;
		default:
			ItemBorder->SetBrushColor(FLinearColor::Black);
		}
		// 이미지 아이콘 지정 코드
		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);

		// 아이템 스택으로 쌓기 여부 코드
		if (ItemReference->ItemNumericData.bIsStackable)
		{
			// 쌓는다면 아이콘 위에 숫자로 개수 표시를 하고
			ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity));
		}
		else
		{
			// 안쌓는다면 개수 표시부분을 끈다
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
		// 드래그 했을때 임시객체 추가
		// 투명하게 보이는 아이템 박스를 생성
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);

		// 아이템의 위젯설정값 받아오는
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());
		DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity));

		// 아이템의 스택으로 쌓기 가능여부
		// 참 이라면 출력, 거짓이라면 숨기기
		ItemReference->ItemNumericData.bIsStackable ?
			DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->ItemQuantity))
			: DragVisual->ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;
		
		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;
		
		OutOperation = DragItemOperation;
	}
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
