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
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

//====================================================================================
//  마우스 커서 이동을 제공하는 플레이어 컨트롤러
//====================================================================================
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
	TObjectPtr<UNiagaraSystem> FxCursor;

	//====================================================================================
	//  IMC, IA Section
	//====================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MouseInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraRotationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlusSignAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MinusSignAction;


	//====================================================================================
	//  Owner Section
	//====================================================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<APlayerCharacter> OwnerCharacter;


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	bool bMoveToMouseCursor;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();


	//====================================================================================
	//  Binding Funtion Section
	//====================================================================================
protected:
	// Camera Zoom Up/Down
	void OnWheelAction(const FInputActionValue& Value);

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	void CameraZoom(const FInputActionValue& Value);
	void CameraRotate(const FInputActionValue& Value);

	void StartJump();
	void StopJump();

	void Attack();

	// Interaction IA
	void BeginInteract();
	void EndInteract();

	// Inventory IA
	void ToggleMenu();

	// Modify Stat
	void ModifyStat(const FInputActionValue& Value);
public:
	void SetDisableInput();

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed

};
