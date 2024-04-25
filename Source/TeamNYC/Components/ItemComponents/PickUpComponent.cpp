#include "Components/ItemComponents/PickUpComponent.h"
#include "Item/ItemBase/ItemBase.h"
#include "Item/LootItem.h"

UPickUpComponent::UPickUpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPickUpComponent::InitializePickup(TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	ALootItem* OwnerPtr = Cast<ALootItem>(GetOwner());
	bool bIsValidItem = OwnerPtr->ItemDataTable && !OwnerPtr->DesiredItemID.IsNone();
	if (bIsValidItem) {
		const FItemData* ItemDataRow = OwnerPtr->ItemDataTable->FindRow<FItemData>(
			OwnerPtr->DesiredItemID, OwnerPtr->DesiredItemID.ToString());
		OwnerPtr->ItemReference = NewObject<UItemBase>(this, BaseClass);

		OwnerPtr->ItemReference->ItemID = ItemDataRow->ItemID;
		OwnerPtr->ItemReference->ItemType = ItemDataRow->ItemType;
		OwnerPtr->ItemReference->ItemQuality = ItemDataRow->ItemQuality;
		OwnerPtr->ItemReference->ItemNumericData = ItemDataRow->ItemNumericData;
		OwnerPtr->ItemReference->ItemTextData = ItemDataRow->ItemTextData;
		OwnerPtr->ItemReference->ItemAssetData = ItemDataRow->ItemAssetData;
		OwnerPtr->ItemReference->ItemStatistics = ItemDataRow->ItemStatistics;
		OwnerPtr->ItemReference->CharacterStatistics = ItemDataRow->CharacterStatistics;

		InQuantity <= 0 ? OwnerPtr->ItemReference->SetQuantity(1) : OwnerPtr->ItemReference->SetQuantity(InQuantity);

		OwnerPtr->ItemMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);

		OwnerPtr->UpdateInteractableData();
	}
}