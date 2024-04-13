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
		DamageValue->SetVisibility(ESlateVisibility::Visible);
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
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorValue->SetVisibility(ESlateVisibility::Collapsed);
		SellValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Quest:
		ItemType->SetText(FText::FromString("Quest"));
		break;
	case EItemType::Mundane:
		ItemType->SetText(FText::FromString("Mundane"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorValue->SetVisibility(ESlateVisibility::Collapsed);
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		SellValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:;
	}
	
	// �̸�
	ItemName->SetText(ItemBeingHovered->ItemTextData.Name);

	// �������� �ִ��� �Ǻ��� �ִٸ� ���� �־��ְ� ������ ��� ����
	if (ItemBeingHovered->ItemStatistics.DamageValue > 0)
	{
		DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
	}
	else
	{
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		//DamageLabel->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	// ������ �ִ��� �Ǻ��� �ִٸ� ���� �־��ְ� ������ ��� ����
	if (ItemBeingHovered->ItemStatistics.ArmorValue > 0)
	{
		ArmorValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorValue));
	}
	else
	{
		ArmorValue->SetVisibility(ESlateVisibility::Collapsed);
		//ArmorLabel->SetVisibility(ESlateVisibility::Collapsed);
	}

	// �Ǹ� ����
	SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));
	
	// ����
	UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);

	// ������ ����
	ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);
	
	// ���� ����
	StackWeightValue->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));
	//StackWeightValue->SetText(FText::FromString(WeightInfo));

	if (ItemBeingHovered->ItemNumericData.bIsStackable)
	{
		MaxStackSizeText->SetText(FText::AsNumber(ItemBeingHovered->ItemNumericData.MaxStackSize));
	}
	else
	{
		MaxStackSizeText->SetVisibility(ESlateVisibility::Collapsed);
	}	
}
