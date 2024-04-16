#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	// Item Quality
	Useless		UMETA(DisplayName = "Useless"),		// 회색
	Shoddy		UMETA(DisplayName = "Shoddy"),		// 흰색
	Common		UMETA(DisplayName = "Common"),		// 초록
	Rare		UMETA(DisplayName = "Rare"),		// 파랑
	Epic		UMETA(DisplayName = "Epic"),		// 보라
	Unique		UMETA(DisplayName = "Unique"),		// 청록
	Masterpiece	UMETA(DisplayName = "Masterpiece"),	// 레드
	Mythic		UMETA(DisplayName = "Mythic"),		// 노랑
	Legendary	UMETA(DisplayName = "Legendary"),	// 주황
};

UENUM()
enum class EItemType : uint8
{
	//Item Slot Type
	Junk		UMETA(DisplayName = "Junk"),
	Tool		UMETA(DisplayName = "Tool"),
	Armor		UMETA(DisplayName = "Armor"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Shield		UMETA(DisplayName = "Shield"),
	Spell		UMETA(DisplayName = "Spell"),
	Ammo		UMETA(DisplayName = "Ammo"),
	Consumable	UMETA(DisplayName = "Consumable"),
	Quest		UMETA(DisplayName = "Quest"),
	Mundane		UMETA(DisplayName = "Mundane"),
};

USTRUCT()
struct FItemStatistics
{
	GENERATED_USTRUCT_BODY()

	// 최대 체력
	UPROPERTY(EditAnywhere)
	float AdditionalHp{};

	// 공격력
	UPROPERTY(EditAnywhere)
	float Damage{};

	// 방어력
	UPROPERTY(EditAnywhere)
	float Armor{};

	// 공격사거리
	UPROPERTY(EditAnywhere)
	float AttackRange{};

	// 공격속도
	UPROPERTY(EditAnywhere)
	float AttackSpeed{};

	// 이동속도
	UPROPERTY(EditAnywhere)
	float MovementSpeed{};

	// 복구금액 -> 다시사기
	UPROPERTY(EditAnywhere)
	float RestorationAmount{};

	// 팔기금액
	UPROPERTY(EditAnywhere)
	float SellValue{};
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name{};

	UPROPERTY(EditAnywhere)
	FText Description{};

	UPROPERTY(EditAnywhere)
	FText InteractionText{};

	UPROPERTY(EditAnywhere)
	FText UsageText{};

	UPROPERTY(EditAnywhere)
	FText WhenUsedText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Weight{};

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize{};

	UPROPERTY(EditAnywhere)
	bool bIsStackable{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	bool bIsQuestItem;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon{};

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh{};
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ItemID{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics ItemStatistics{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData ItemTextData{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData{};

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData ItemAssetData{};
};