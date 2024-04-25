#pragma once
#include "CoreMinimal.h"
#include "Components/InventoryComponents/InventoryComponent.h"
#include "Data/ItemDataStruct/ItemDataStructs.h"
#include "Data/CharacterStat.h"
#include "ItemBase.generated.h"

class APlayerCharacter;
struct FCharacterStat;

UCLASS()
class TEAMNYC_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	//====================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================
	UPROPERTY();
	UInventoryComponent* OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ItemID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FCharacterStat CharacterStatistics;	

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData ItemAssetData;

	bool bIsPickup;
	bool bIsCopy;
public:
	//====================================================================================
	// FUNCTIONS
	//====================================================================================
	UItemBase();

	void ResetItemFlags();

	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	// 아이템 스택의 총 무게
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return ItemQuantity * ItemNumericData.Weight; };

	// 아이템 단일의 무게
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; };

	// 최고 스택인지 비교하는 함수
	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return ItemQuantity == ItemNumericData.MaxStackSize; };

	// TODO:
	// 매개변수들을 protected로 변경예정

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(APlayerCharacter* Character);
protected:
	//====================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================
	bool operator ==(const FName& OtherID) const
	{
		return this->ItemID == OtherID;
	}
protected:
	//====================================================================================
	// FUNCTIONS
	//====================================================================================

};
