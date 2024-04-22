// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Pickup.h"

#include "Item/ItemBase/ItemBase.h"
#include "Character/Player/PlayerCharacter.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetCanEverAffectNavigation(false);
	SetRootComponent(PickupMesh);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}

void APickup::InitializePickup(TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->ItemID =					ItemDataRow->ItemID;
		ItemReference->ItemType =				ItemDataRow->ItemType;
		ItemReference->ItemQuality =			ItemDataRow->ItemQuality;
		ItemReference->ItemNumericData =		ItemDataRow->ItemNumericData;
		ItemReference->ItemTextData =			ItemDataRow->ItemTextData;
		ItemReference->ItemAssetData =			ItemDataRow->ItemAssetData;
		ItemReference->ItemStatistics =			ItemDataRow->ItemStatistics;
		ItemReference->CharacterStatistics =	ItemDataRow->CharacterStatistics;

		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		PickupMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);

		UpdateInteractableData();
	}
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
	ItemReference->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	ItemReference->OwningInventory = nullptr;
	PickupMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	UpdateInteractableData();
}

void APickup::BeginFocus()
{
	IInteractionInterface::BeginFocus();
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
	IInteractionInterface::EndFocus();
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(APlayerCharacter* PlayerCharacter)
{
	//IInteractionInterface::Interact(PlayerCharacter);

	if (PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

void APickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.Name;
	InstanceInteractableData.Quantity = ItemReference->ItemQuantity;

	InteractableData = InstanceInteractableData;
}

void APickup::TakePickup(const APlayerCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

				switch (AddResult.OperationResult)
				{
					// 객체 아무것도 아닐때
				case EItemAddResult::IAR_NoItemAdded:
					break;
					// 객체 업데이트용(상호작용)
				case EItemAddResult::IAR_PartialAmountItemAdded:
					UpdateInteractableData();
					Taker->UpdateInteractionWidget();			
					break;
					// 객체 삭제용(아이템)
				case EItemAddResult::IAR_AllItemsAdded:
					Destroy();
					break;
				default:;
				}
				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Inventory Component is null!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was null!"))
		}
	}
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ?
		PropertyChangedEvent.Property->GetFName() :
		NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
	{
		if (ItemDataTable)
		{
			if (const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				PickupMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);
			}
		}
	}
}

