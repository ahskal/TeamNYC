#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface/InteractionInterface.h"
#include "LootItem.generated.h"

class UPickUpComponent;
class UDropComponent;
class UItemBase;

UCLASS(ClassGroup = (Item))
class TEAMNYC_API ALootItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	friend UPickUpComponent;
	friend UDropComponent;
public:	
	ALootItem();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;

	void InitializePickup(TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	//virtual void BeginInteract() override;
	//virtual void EndInteract() override;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Item | Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditInstanceOnly, Category = "Item | Item Database")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Item | Item Database")
	FName DesiredItemID;

	UPROPERTY(EditInstanceOnly, Category = "Item | Item Database")
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere, Category = "Item | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Item | Interaction")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPickUpComponent> PickUpComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDropComponent> DropComponent;


	virtual void BeginPlay() override;
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	void UpdateInteractableData();
	void TakePickup(const APlayerCharacter* Taker);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
private:
};
