#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	// Item Quality
	Useless		UMETA(DisplayName = "Useless"),
	Shoddy		UMETA(DisplayName = "Shoddy"),
	Common		UMETA(DisplayName = "Common"),
	Rare		UMETA(DisplayName = "Rare"),
	Epic		UMETA(DisplayName = "Epic"),
	Unique		UMETA(DisplayName = "Unique"),
	Masterpiece	UMETA(DisplayName = "Masterpiece"),
	Mythic		UMETA(DisplayName = "Mythic"),
	Legendary	UMETA(DisplayName = "Legendary"),
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

	UPROPERTY(EditAnywhere)
	float ArmorRating{};

	UPROPERTY(EditAnywhere)
	float DamageValue{};

	UPROPERTY(EditAnywhere)
	float RestorationAmount{};

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