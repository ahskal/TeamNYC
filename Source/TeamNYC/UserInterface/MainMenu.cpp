#include "UserInterface/MainMenu.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

#include "Item/ItemBase/ItemBase.h"
#include "Character/Player/PlayerCharacter.h"


void UMainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);
	if (PlayerCharacter && ItemDragDrop && ItemDragDrop->SourceItem)
	{
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->ItemQuantity);
		return true;
	}
	return false;
}