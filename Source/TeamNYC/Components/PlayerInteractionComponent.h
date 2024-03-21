// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

class IInteractionInterface;
class UInventoryComponent;
class APlayerHUD;
class UItemBase;

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.f) {};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMNYC_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPlayerInteractionComponent();
	
	void UpdateInteractionWidget() const;

	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; }
	FORCEINLINE bool bIsInteracting() const { return GetOwner()->GetWorldTimerManager().IsTimerActive(TimerHandleInteraction); };

	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);

	void BeginInteract();
	void EndInteract();
	void ToggleMenu();

protected:
	APlayerHUD* HUD;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	UInventoryComponent* PlayerInventory;

	float InteractionCheckFrequency;
	float InteractionCheckDistance;

	FTimerHandle TimerHandleInteraction;
	FInteractionData InteractionData;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	
	void Interact();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
};