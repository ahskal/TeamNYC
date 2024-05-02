// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KeyboardPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//====================================================================================
//  WASD 움직임을 제공하는 플레이어 컨트롤러
//====================================================================================
UCLASS()
class TEAMNYC_API AKeyboardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	// OwnerPawn
	UPROPERTY(VisibleAnywhere, Category = "Owner")
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY(VisibleAnywhere, Category = "Owner")
	TObjectPtr<ACharacter> OwnerCharacter;

	// Controller
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<AController> Controller;

	// MappingContext
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> KeyboardInputMappingContext;

	// Move IA
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// Jump IA
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	// Look IA
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	// WalkSlow IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//TObjectPtr<UInputAction> WalkSlowAction;

	// WalkFast IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//TObjectPtr<UInputAction> WalkFastAction;

	// Attack IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//TObjectPtr<UInputAction> AttackAction;

	// Interaction IA
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractionAction;

public:
	AKeyboardPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	//void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();

	void BeginInteract();
	void EndInteract();
};
