#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryTooltip.h"

#include "Item/ItemBase/ItemBase.h"
#include "Components/TextBlock.h"
#include "Util/ColorConstants.h"

#define BLUE FLinearColor(0.0f, 0.2f, 1.0f)
#define ORANGE FLinearColor(1.0f, 0.15f, 0.0f)
#define GOLD FLinearColor(0.97f, 0.8f, 0.0f)
#define CYAN FLinearColor(0, 1.f, 1.f)

void UInventoryTooltip::NativeConstruct()
{
	//Super::NativeConstruct();
	//UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();
	//
	//switch (ItemBeingHovered->ItemType) {
	//case EItemType::Junk:
	//	ItemType->SetText(FText::FromString("Junk"));
	//	break;
	//case EItemType::Tool:
	//	ItemType->SetText(FText::FromString("Tool"));
	//	break;
	//case EItemType::Armor:
	//	ItemType->SetText(FText::FromString("Armor"));
	//	break;
	//case EItemType::Weapon:
	//	ItemType->SetText(FText::FromString("Weapon"));
	//	DamageValue->SetVisibility(ESlateVisibility::Visible);
	//	break;
	//case EItemType::Shield:
	//	ItemType->SetText(FText::FromString("Shield"));
	//	break;
	//case EItemType::Spell:
	//	ItemType->SetText(FText::FromString("Spell"));
	//	break;
	//case EItemType::Ammo:
	//	ItemType->SetText(FText::FromString("Ammo"));
	//	break;
	//case EItemType::Consumable:
	//	ItemType->SetText(FText::FromString("Consumable"));
	//	break;
	//case EItemType::Mundane:
	//	ItemType->SetText(FText::FromString("Mundane"));
	//	break;
	//default:;
	//}
	//
	//if (ItemBeingHovered->ItemNumericData.bIsQuestItem)
	//{
	//	QuestText->SetColorAndOpacity(GOLD);
	//	QuestText->SetText(FText::FromString("~Quest~"));
	//}
	//else
	//{
	//	QuestText->SetVisibility(ESlateVisibility::Collapsed);
	//}
	//
	//if (ItemBeingHovered)
	//{
	//	switch (ItemBeingHovered->ItemQuality)
	//	{
	//	case EItemQuality::Useless:
	//		ItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
	//		QualityText->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
	//		QualityText->SetText(FText::FromString("Useless"));
	//		break;
	//	case EItemQuality::Shoddy:
	//		ItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
	//		QualityText->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
	//		QualityText->SetText(FText::FromString("Shoddy"));
	//		break;
	//	case EItemQuality::Common:
	//		ItemName->SetColorAndOpacity(FLinearColor::White);
	//		QualityText->SetColorAndOpacity(FLinearColor::White);
	//		QualityText->SetText(FText::FromString("Common"));
	//		break;
	//	case EItemQuality::Rare:
	//		ItemName->SetColorAndOpacity(FLinearColor::Green);
	//		QualityText->SetColorAndOpacity(FLinearColor::Green);
	//		QualityText->SetText(FText::FromString("Rare"));
	//		break;
	//	case EItemQuality::Epic:
	//		ItemName->SetColorAndOpacity(BLUE);
	//		QualityText->SetColorAndOpacity(BLUE);
	//		QualityText->SetText(FText::FromString("Epic"));
	//		break;
	//	case EItemQuality::Legendary:
	//		ItemName->SetColorAndOpacity(UE::Geometry::LinearColors::Purple3f());
	//		QualityText->SetColorAndOpacity(UE::Geometry::LinearColors::Purple3f());
	//		QualityText->SetText(FText::FromString("Legendary"));
	//		break;
	//	case EItemQuality::Mythic:
	//		ItemName->SetColorAndOpacity(GOLD);
	//		QualityText->SetColorAndOpacity(GOLD);
	//		QualityText->SetText(FText::FromString("Mythic"));
	//		break;
	//	case EItemQuality::Unique:
	//		ItemName->SetColorAndOpacity(ORANGE);
	//		QualityText->SetColorAndOpacity(ORANGE);
	//		QualityText->SetText(FText::FromString("Unique"));
	//		break;
	//	default:
	//		ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	//		QualityText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	//		;
	//	}
	//}
	//ItemName->SetText(ItemBeingHovered->ItemTextData.Name);
	//
	//
	//if (ItemBeingHovered->ItemStatistics.DamageValue > 0)
	//{
	//	DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
	//}
	//else
	//{
	//	DamageValue->SetVisibility(ESlateVisibility::Collapsed);
	//	DamageLabel->SetVisibility(ESlateVisibility::Collapsed);
	//}
	//
	//if (ItemBeingHovered->ItemStatistics.ArmorRating > 0)
	//{
	//	ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
	//}
	//else
	//{
	//	ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
	//	ArmorLabel->SetVisibility(ESlateVisibility::Collapsed);
	//}
	//
	//SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));
	//ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);
	//
	//const FString WeightInfo = { FString::SanitizeFloat(ItemBeingHovered->GetItemStackWeight()) };
	//
	//StackWeightValue->SetText(FText::FromString(WeightInfo));
	//
	//if (ItemBeingHovered->ItemNumericData.bIsStackable)
	//{
	//	StackSizeText->SetText(FText::AsNumber(ItemBeingHovered->ItemNumericData.MaxStackSize));
	//
	//}
	//else
	//{
	//	StackSizeText->SetVisibility(ESlateVisibility::Collapsed);
	//	StackSizeLabel->SetVisibility(ESlateVisibility::Collapsed);
	//}
}
