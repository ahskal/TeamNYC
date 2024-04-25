#include "Item/LootItem.h"
#include "Item/ItemBase/ItemBase.h"

#include "Components/ItemComponents/PickUpComponent.h"
#include "Components/ItemComponents/DropComponent.h"

#include "Character/Player/PlayerCharacter.h"

ALootItem::ALootItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetCanEverAffectNavigation(false);
	SetRootComponent(ItemMesh);

	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("UPickUpComponent"));
	DropComponent = CreateDefaultSubobject<UDropComponent>(TEXT("UDropComponent"));
}

void ALootItem::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}

void ALootItem::Interact(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

void ALootItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALootItem::BeginFocus()
{
	IInteractionInterface::BeginFocus();
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void ALootItem::EndFocus()
{
	IInteractionInterface::EndFocus();
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(false);
	}
}

void ALootItem::InitializePickup(TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	PickUpComponent->InitializePickup(BaseClass, InQuantity);
}

void ALootItem::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	DropComponent->InitializeDrop(ItemToDrop, InQuantity);
}

void ALootItem::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Loot;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.Name;
	InstanceInteractableData.Quantity = ItemReference->ItemQuantity;

	InteractableData = InstanceInteractableData;
}

void ALootItem::TakePickup(const APlayerCharacter* Taker)
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
				UE_LOG(LogTemp, Warning, TEXT("플레이어의 인벤토리가 가득찼습니다."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("아이템의 내부 참조값이 없습니다."))
		}
	}
}

void ALootItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ?
		PropertyChangedEvent.Property->GetFName() :
		NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(ALootItem, DesiredItemID))
	{
		if (ItemDataTable)
		{
			if (const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				ItemMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);
			}
		}
	}
}
