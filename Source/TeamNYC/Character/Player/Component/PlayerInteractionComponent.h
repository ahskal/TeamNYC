// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

class IInteractionInterface;
class APlayerHUD;

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.f)
	{

	};

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
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	FTimerHandle TimerHandleInteraction;
	FInteractionData InteractionData;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void Interact();
	 
	void ToggleMenu();
	void UpdateInteractionWidget() const;

	APlayerHUD* HUD;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE bool bIsInteracting() const { return GetOwner()->GetWorldTimerManager().IsTimerActive(TimerHandleInteraction); };

	void BeginInteract();
	void EndInteract();

};