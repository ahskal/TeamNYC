// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterPrototype.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class IInteractionInterface;

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

UCLASS()
class TEAMNYC_API APlayerCharacter : public ACharacterPrototype
{
	GENERATED_BODY()
	
	
private:
	// SpringArm
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent*	SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent*		Camera;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

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
public:
	APlayerCharacter();

	FORCEINLINE bool bIsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandleInteraction); };
	
	void BeginInteract();
	void EndInteract();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
