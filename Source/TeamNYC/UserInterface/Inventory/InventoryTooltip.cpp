#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Item/ItemBase/ItemBase.h"
#include "Components/TextBlock.h"
#include "Util/ColorConstants.h"

#define BLUE FLinearColor(0.0f, 0.2f, 1.0f)
#define ORANGE FLinearColor(1.0f, 0.15f, 0.0f)
#define GOLD FLinearColor(0.97f, 0.8f, 0.0f)
#define CYAN FLinearColor(0, 1.f, 1.f)

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType) {
	case EItemType::Junk:
		ItemType->SetText(FText::FromString("Junk"));
		break;
	case EItemType::Tool:
		ItemType->SetText(FText::FromString("Tool"));
		break;
	case EItemType::Armor:
		ItemType->SetText(FText::FromString("Armor"));
		break;
	case EItemType::Weapon:
		ItemType->SetText(FText::FromString("Weapon"));
		Damage->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItemType::Shield:
		ItemType->SetText(FText::FromString("Shield"));
		break;
	case EItemType::Spell:
		ItemType->SetText(FText::FromString("Spell"));
		break;
	case EItemType::Ammo:
		ItemType->SetText(FText::FromString("Ammo"));
		break;
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString("Consumable"));
		Damage->SetVisibility(ESlateVisibility::Collapsed);
		Armor->SetVisibility(ESlateVisibility::Collapsed);
		SellValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Quest:
		ItemType->SetText(FText::FromString("Quest"));
		break;
	case EItemType::Mundane:
		ItemType->SetText(FText::FromString("Mundane"));
		break;
	default:;
	}

	// 이름
	ItemName->SetText(FText::Format(FText::FromString("{0} : {1}"), FText::FromString("Name"), ItemBeingHovered->ItemTextData.Name));

	SetTextBlockValue(AdditionalHp, ItemBeingHovered->ItemStatistics.AdditionalHp, FText::FromString("Type"));
	SetTextBlockValue(Damage, ItemBeingHovered->ItemStatistics.Damage, FText::FromString("Damage"));
	SetTextBlockValue(Armor, ItemBeingHovered->ItemStatistics.Armor, FText::FromString("Armor"));
	SetTextBlockValue(AttackRange, ItemBeingHovered->ItemStatistics.AttackRange, FText::FromString("AttackRange"));
	SetTextBlockValue(AttackSpeed, ItemBeingHovered->ItemStatistics.AttackSpeed, FText::FromString("AttackSpeed"));
	SetTextBlockValue(MovementSpeed, ItemBeingHovered->ItemStatistics.MovementSpeed, FText::FromString("MovementSpeed"));

	SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));

	UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);

	ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);

	StackWeightValue->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));

	if (ItemBeingHovered->ItemNumericData.bIsStackable)
	{
		MaxStackSizeText->SetText(FText::AsNumber(ItemBeingHovered->ItemNumericData.MaxStackSize));
	}
	else
	{
		MaxStackSizeText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventoryTooltip::SetTextBlockValue(UTextBlock* TextBlock, int32 Value, FText Text)
{
	if (Value > 0)
	{
		if (Text.IsEmpty()) {

		}
		TextBlock->SetText(FText::Format(FText::FromString("{0} : {1}"), Text, FText::AsNumber(Value)));
	}
	else
	{
		TextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}