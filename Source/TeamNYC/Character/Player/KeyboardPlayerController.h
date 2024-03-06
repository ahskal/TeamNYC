// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KeyboardPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**********************************************
 * WASD 움직임을 제공하는 플레이어 컨트롤러
 **********************************************/
UCLASS()
class TEAMNYC_API AKeyboardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	// OwnerPawn
	UPROPERTY(VisibleAnywhere, Category = "Owner")
	APawn* OwnerPawn{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Owner")
	ACharacter* OwnerCharacter{ nullptr };

	// Controller
	UPROPERTY(VisibleAnywhere, Category = "Input")
	AController* Controller{ nullptr };

	// MappingContext
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// Move IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Jump IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Look IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	// WalkSlow IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* WalkSlowAction;

	// WalkFast IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* WalkFastAction;

	// Attack IA
	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* AttackAction;

	// Look IA
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractionAction;

public:
	AKeyboardPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	//void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);

	void BeginInteraction(const FInputActionValue& Value);
	void EndInteraction(const FInputActionValue& Value);
};
