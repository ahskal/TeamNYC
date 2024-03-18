// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class APlayerCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class TEAMNYC_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMousePlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FxCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MouseInputMappingContext;

	// Click IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftClickAction;

	// Click IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RightClickAction;

	// Jump IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	// Interaction IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

private:
	// OwnerPawn
	UPROPERTY(VisibleAnywhere, Category = "Owner")
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY(VisibleAnywhere, Category = "Owner")
	TObjectPtr<APlayerCharacter> OwnerCharacter;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	bool bMoveToMouseCursor;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	void StartJump();
	void StopJump();

	void BeginInteract();
	void EndInteract();

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed

};
