#include "Components/ItemComponents/DropComponent.h"
#include "Item/ItemBase/ItemBase.h"
#include "Item/LootItem.h"

UDropComponent::UDropComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDropComponent::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ALootItem* ItemTemp = Cast<ALootItem>(GetOwner());

	ItemTemp->ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemTemp->ItemReference->SetQuantity(1) : ItemTemp->ItemReference->SetQuantity(InQuantity);
	ItemTemp->ItemReference->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	ItemTemp->ItemReference->OwningInventory = nullptr;
	ItemTemp->ItemMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	ItemTemp->UpdateInteractableData();
}
