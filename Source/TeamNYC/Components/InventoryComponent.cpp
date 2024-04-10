#include "Components/InventoryComponent.h"

#include "Item/ItemBase/ItemBase.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FItemAddResult UInventoryComponent::HandleAddItem(UItemBase* InputItem)
{
	if (GetOwner())
	{
		const int32 InitialRequestedAddAmount = InputItem->ItemQuantity;

		//handle non-stackable items
		if (!InputItem->ItemNumericData.bIsStackable)
		{
			return HandleNonStackableItems(InputItem);
		}

		const int32 StackableAmountAdded = HandleStackableItems(InputItem, InitialRequestedAddAmount);

		if (StackableAmountAdded == InitialRequestedAddAmount)
		{
			//return added all result
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format(
				FText::FromString("{0} {1} added to inventory."), InitialRequestedAddAmount, InputItem->ItemTextData.Name));
		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			//return added partial result
			return FItemAddResult::AddedPartial(InitialRequestedAddAmount, FText::Format(
				FText::FromString("Partial amount {0} of {1} added to inventory."), InitialRequestedAddAmount, InputItem->ItemTextData.Name));
		}

		if (StackableAmountAdded <= 0)
		{
			//return added none result
			return FItemAddResult::AddedNone(FText::Format(
				FText::FromString("Unable to add {0} to inventory. Inventory is full or item is invalid."), InputItem->ItemTextData.Name));
		}
	}
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner check failed somehow."));
}

UItemBase* UInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn);
		if (Result)
		{
			return *Result;
		}
	}
	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	const TArray<TObjectPtr<UItemBase>>::ElementType* Result =
		InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
	{
		return InventoryItem->ItemID == ItemIn->ItemID && !InventoryItem->IsFullItemStack();
	}
	);

	if (Result)
	{
		return *Result;
	}

	return nullptr;
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);

	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->ItemQuantity);

	ItemIn->SetQuantity(ItemIn->ItemQuantity - ActualAmountToRemove);

	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	
	if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandleNonStackableItems(UItemBase* ItemIn)
{
	//check for valid weight
	if (FMath::IsNearlyZero(ItemIn->GetItemSingleWeight()) || ItemIn->GetItemSingleWeight() < 0)
	{
		//return added none
		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to inventory. Item has invalid weight."), ItemIn->ItemTextData.Name));
	}

	if (InventoryTotalWeight + ItemIn->GetItemSingleWeight() > GetWeightCapacity())
	{
		//return added none

		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to inventory. Weight capacity exceeded."), ItemIn->ItemTextData.Name));

	}

	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		//return added none

		return FItemAddResult::AddedNone(FText::Format(
			FText::FromString("Could not add {0} to inventory. Inventory is full."), ItemIn->ItemTextData.Name));

	}

	AddNewItem(ItemIn, 1);
	//return added all result

	return FItemAddResult::AddedAll(1, FText::Format(
		FText::FromString("{0} added to inventory."), ItemIn->ItemTextData.Name));
}

int32 UInventoryComponent::HandleStackableItems(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	if (RequestedAddAmount <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		//invalid item data
		return 0;
	}

	int32 AmountToDistribute = RequestedAddAmount;

	//check if item already exists as a partial stack in the inventory
	UItemBase* ExistingItemStack = FindNextPartialStack(ItemIn);

	while (ExistingItemStack)
	{
		//calculate how many of the existing item would be needed to make the next stack full
		const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItemStack, AmountToDistribute);
		//calculate how many of the AmountToMakeFullStack can actually be carried based on weight capacity
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ExistingItemStack, AmountToMakeFullStack);

		//as long as the remaining number of items does not exceed weight capacity this will be true
		if (WeightLimitAddAmount > 0)
		{
			//adjust the existing item stack quantity and inventory total weight
			ExistingItemStack->SetQuantity(ExistingItemStack->ItemQuantity + WeightLimitAddAmount);
			InventoryTotalWeight += (ExistingItemStack->GetItemSingleWeight() * WeightLimitAddAmount);

			//adjust the count to be distributed
			AmountToDistribute -= WeightLimitAddAmount;

			//set count of the item remaining on the ground
			ItemIn->SetQuantity(AmountToDistribute);

			//TODO: Refine this logic as > capacity should never be possible
			//if max weight capacity is reached no need to run the loop again
			if (InventoryTotalWeight + ExistingItemStack->GetItemSingleWeight() > InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
		}
		else if (WeightLimitAddAmount <= 0)
		{
			if (AmountToDistribute != RequestedAddAmount)
			{
				//this block of code will be reached if distributing an item across multiple stacks
				//and the weight limit is hit during the process
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}
			//reached if there is a partial stack but none of it can be added
			return 0;
		}

		if (AmountToDistribute <= 0)
		{
			//all of the input item was distributed across existing stack(s)
			OnInventoryUpdated.Broadcast();
			return RequestedAddAmount;
		}
		//check for another existing partial stack
		ExistingItemStack = FindNextPartialStack(ItemIn);
	}

	//no more partial stacks found, check if a new stack can be added
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		//attempt to add as many of the remaining item quantity as possible to a new stack based on weight
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ItemIn, AmountToDistribute);

		if (WeightLimitAddAmount > 0)
		{
			//if there are more items to distribute but weight limit has been reached
			if (WeightLimitAddAmount < AmountToDistribute)
			{
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetQuantity(AmountToDistribute);

				//create a copy as part of the stack remaining on the ground is being added
				AddNewItem(ItemIn->CreateItemCopy(), WeightLimitAddAmount);
				return RequestedAddAmount - AmountToDistribute;
			}
			//entire stack from ground can be added so no need for a copy, as the original will be destroyed
			AddNewItem(ItemIn, AmountToDistribute);
			return RequestedAddAmount;
		}

		//reached if there are free item slots but no remaining weight capacity
		return RequestedAddAmount - AmountToDistribute;
	}

	//can only be reached if there is no existing stack and no empty capacity slots
	return 0;
}

float UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount =
		FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetItemSingleWeight());

	if (WeightMaxAddAmount > RequestedAddAmount)
	{
		return RequestedAddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount)
{
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->ItemQuantity;

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;

	if (Item->bIsCopy || Item->bIsPickup)
	{
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();

	OnInventoryUpdated.Broadcast();
}

