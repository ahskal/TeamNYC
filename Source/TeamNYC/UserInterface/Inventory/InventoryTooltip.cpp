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
	
	// 이름
	ItemName->SetText(ItemBeingHovered->ItemTextData.Name);

	// 데미지가 있는지 판별식 있다면 값을 넣어주고 없으면 출력 끄기
	if (ItemBeingHovered->ItemStatistics.DamageValue > 0)
	{
		DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
	}
	else
	{
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		//DamageLabel->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	// 방어력이 있는지 판별식 있다면 값을 넣어주고 없으면 출력 끄기
	if (ItemBeingHovered->ItemStatistics.ArmorValue > 0)
	{
		ArmorValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorValue));
	}
	else
	{
		ArmorValue->SetVisibility(ESlateVisibility::Collapsed);
		//ArmorLabel->SetVisibility(ESlateVisibility::Collapsed);
	}

	// 판매 가격
	SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));
	
	// 설명
	UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);

	// 아이템 설명
	ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);
	
	// 현재 갯수
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
