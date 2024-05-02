#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Item/ItemBase/ItemBase.h"
#include "Data/CharacterStat.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Border.h"
#include "Util/ColorConstants.h"

#define BLUE FLinearColor(0.f, 0.2f, 1.f)
#define ORANGE FLinearColor(1.f, 0.15f, 0.f)
#define GOLD FLinearColor(0.97f, 0.8f, 0.f)
#define CYAN FLinearColor(0.f, 1.f, 1.f)
#define PURPLE FLinearColor(0.3f, 0.f, 1.f)

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->ItemType) {
	case EItemType::Junk:
		ItemType->SetText(FText::FromString(TEXT("쓰레기")));


		break;
	case EItemType::Tool:
		ItemType->SetText(FText::FromString(TEXT("도구")));


		break;
	case EItemType::Armor:
		ItemType->SetText(FText::FromString(TEXT("방어구")));


		break;
	case EItemType::Weapon:
		ItemType->SetText(FText::FromString(TEXT("무기")));


		break;
	case EItemType::Shield:
		ItemType->SetText(FText::FromString(TEXT("방패")));


		break;
	case EItemType::Spell:
		ItemType->SetText(FText::FromString(TEXT("주문")));


		break;
	case EItemType::Ammo:
		ItemType->SetText(FText::FromString(TEXT("탄약")));


		break;
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString(TEXT("소모품")));


		break;
	case EItemType::Quest:
		ItemType->SetText(FText::FromString(TEXT("퀘스트")));


		break;
	case EItemType::Mundane:
		ItemType->SetText(FText::FromString(TEXT("평범한")));


		break;
	default:;
	}

	if (ItemBeingHovered) {
		switch (ItemBeingHovered->ItemQuality)
		{
		case EItemQuality::Useless:
			ItemName->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
			ItemBorder->SetBrushColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.f));
			break;
		case EItemQuality::Shoddy:
			ItemName->SetColorAndOpacity(FLinearColor::Gray);
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemName->SetColorAndOpacity(UE::Geometry::LinearColors::DarkCyan3b());
			ItemBorder->SetBrushColor(UE::Geometry::LinearColors::DarkCyan3b());
			break;
		case EItemQuality::Rare:
			ItemName->SetColorAndOpacity(FLinearColor(0.0f, 0.1f, 1.0f));
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.1f, 1.0f));
			break;
		case EItemQuality::Epic:
			ItemName->SetColorAndOpacity(PURPLE);
			ItemBorder->SetBrushColor(PURPLE);
			break;
		case EItemQuality::Unique:
			ItemName->SetColorAndOpacity(CYAN);
			ItemBorder->SetBrushColor(CYAN);
			break;
		case EItemQuality::Masterpiece:
			ItemName->SetColorAndOpacity(UE::Geometry::LinearColors::Red3b());
			ItemBorder->SetBrushColor(UE::Geometry::LinearColors::Red3b());
			break;
		case EItemQuality::Mythic:
			ItemName->SetColorAndOpacity(GOLD);
			ItemBorder->SetBrushColor(GOLD);
			break;
		case EItemQuality::Legendary:
			ItemName->SetColorAndOpacity(ORANGE);
			ItemBorder->SetBrushColor(ORANGE);
			break;
		default:
			ItemName->SetColorAndOpacity(FLinearColor::Black);
			ItemBorder->SetBrushColor(FLinearColor::Black);
		}
	}

	// 퀘스트 툴팁
	//if (ItemBeingHovered->ItemNumericData.bIsQuestItem)
	//{
	//	QuestText->SetColorAndOpacity(GOLD);
	//	QuestText->SetText(FText::FromString("~Quest~"));
	//}
	//else
	//{
	//	QuestText->SetVisibility(ESlateVisibility::Collapsed);
	//}
	
	// 추가체력, 공격력, 방어력, 사거리, 공속, 이속,	등등
	// 값이 비어있을경우 해당 부분을 켜지 않는다
	bool IsEmpty = ItemBeingHovered->CharacterStatistics.MaxHealthPoint == 0 ||
		ItemBeingHovered->CharacterStatistics.Damage == 0 ||
		//ItemBeingHovered->ItemStatistics.Armor == 0 ||
		ItemBeingHovered->CharacterStatistics.AttackRange == 0 ||
		ItemBeingHovered->CharacterStatistics.AttackSpeed == 0 ||
		ItemBeingHovered->CharacterStatistics.MovementSpeed == 0;
	if (IsEmpty) {
		VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		SetTextBlockTextToText(MaxHp,
			FText::FromString(TEXT("추가 HP ")),
			FText::FromString("+"),
			FText::AsNumber(ItemBeingHovered->CharacterStatistics.MaxHealthPoint));

		SetTextBlockTextToText(Damage,
			FText::FromString(TEXT("공격력 ")),
			FText::FromString("+"),
			FText::AsNumber(ItemBeingHovered->CharacterStatistics.Damage));

		//SetTextBlockTextToText(Armor,
		//	FText::FromString(TEXT("방어력 ")),
		//	FText::FromString("+"),
		//	FText::AsNumber(ItemBeingHovered->ItemStatistics.Armor));

		SetTextBlockTextToText(AttackRange,
			FText::FromString(TEXT("사거리 ")),
			FText::FromString("+"),
			FText::AsNumber(ItemBeingHovered->CharacterStatistics.AttackRange));

		SetTextBlockTextToText(AttackSpeed,
			FText::FromString(TEXT("공격속도 ")),
			FText::FromString("+"),
			FText::AsNumber(ItemBeingHovered->CharacterStatistics.AttackSpeed));

		SetTextBlockTextToText(MovementSpeed,
			FText::FromString(TEXT("이동속도 ")),
			FText::FromString("+"),
			FText::AsNumber(ItemBeingHovered->CharacterStatistics.MovementSpeed));
	}

	// 이름
	SetTextBlockTextToText(ItemName,
		FText::FromString(TEXT("이름 : ")),
		ItemBeingHovered->ItemTextData.Name);
				
	SetTextBlockTextToText(UsageText,
		FText::FromString(TEXT("-용도 : ")),
		ItemBeingHovered->ItemTextData.UsageText);

	SetTextBlockTextToText(ItemDescription,
		FText::FromString(TEXT("-설명 : ")),
		ItemBeingHovered->ItemTextData.Description);

	SetTextBlockTextToText(StackWeightValue,
		FText::FromString(TEXT("무게 : ")),
		FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));

	SetTextBlockTextToText(SellValue, 
		FText::FromString(TEXT("판매가격 : ")),
		FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue),
		FText::FromString(TEXT("원")));
}

// 가변 인수 템플릿
template<typename ...Args>
inline void UInventoryTooltip::SetTextBlockTextToText(UTextBlock* TextBlock, Args ...args)
{
	// 가변 인수 개수 확인
	std::size_t ArgsSize = sizeof...(args);

	// FText로 변환할 문자열
	FString FormatString;

	// 가변 인수들을 순회하며 FText에 포맷 적용
	for (int i = 0; i < ArgsSize; i++) {
		FormatString += FString::Printf(TEXT("{%d}"), i);
	}

	// 가변 인수들로부터 FText 생성
	FText FinalText = FText::Format(FText::FromString(FormatString), args...);

	// UTextBlock에 설정
	TextBlock->SetText(FinalText);
}