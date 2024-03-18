// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Item/ItemBase/ItemDataStructs.h"
#include "ItemBase.generated.h"

class APlayerCharacter;

UCLASS()
class TEAMNYC_API UItemBase : public UObject
{
	GENERATED_BODY()
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

public:
	//====================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================
	//UPROPERTY();
	//UInventoryComponent* OwningInventory;

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

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return ItemQuantity * ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return ItemQuantity == ItemNumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(APlayerCharacter* Character);
};
