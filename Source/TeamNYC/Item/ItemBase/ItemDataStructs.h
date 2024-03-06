#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	// Item Quality
	Shoddy		UMETA(DisplayName = "Shoddy"),
	Common		UMETA(DisplayName = "Common"),
	Quality		UMETA(DisplayName = "Quality"),
	Masterwork	UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster"),
};

UENUM()
enum class EItemType : uint8
{
	//Item Slot Type
	Armor		UMETA(DisplayName = "Armor"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Shield		UMETA(DisplayName = "Shield"),
	Spell		UMETA(DisplayName = "Spell"),
	Consumalbe	UMETA(DisplayName = "Consumalbe"),
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

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FName ID{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemType Type{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemQuality Quality{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemStatistics Statistics{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemTextData TextData{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemNumericData NumericData{};

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemAssetData AssetData{};
};