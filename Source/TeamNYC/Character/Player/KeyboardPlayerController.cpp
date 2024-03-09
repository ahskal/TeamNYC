// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/KeyboardPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "GameFramework/Character.h"


#include "Character/Player/PlayerCharacter.h"

AKeyboardPlayerController::AKeyboardPlayerController()
{
	bShowMouseCursor = true;		// Show the mouse cursor
	bEnableClickEvents = true;		// Enable mouse click events
	bEnableMouseOverEvents = true;	// Enable mouse over events

	// Set DMC
	FString DmcPath = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Assets/Input/IMC_Keyboard.IMC_Keyboard'");
	UInputMappingContext* DmcObj = Cast<UInputMappingContext>(StaticLoadObject(UInputMappingContext::StaticClass(), nullptr, *DmcPath));
	if (DmcObj) KeyboardInputMappingContext = DmcObj;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load DMC: %s"), *DmcPath);

	// Set IA
	// MoveAction
	FString IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Move.IA_Move'");
	UInputAction* IaMove = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaMove) MoveAction = IaMove;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Move: %s"), *IaPath);

	// JumpAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Jump.IA_Jump'");
	UInputAction* IaJump = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaJump) JumpAction = IaJump;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Jump: %s"), *IaPath);

	// JumpAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Interaction.IA_Interaction'");
	UInputAction* IaInter = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaInter) InteractionAction = IaInter;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Jump: %s"), *IaPath);

}

void AKeyboardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode
	SetInputMode(FInputModeGameAndUI());

	// Get PlayerPawn->GetController()
	OwnerPawn = Cast<APawn>(GetPawn());
	if (OwnerPawn)
	{
		//UE_LOG(LogTemp, Display, TEXT("OwnerPawn: %s"), *OwnerPawn->GetName());
		OwnerCharacter = Cast<ACharacter>(OwnerPawn);
		if (OwnerCharacter)
		{
			//UE_LOG(LogTemp, Display, TEXT("OwnerCharacter: %s"), *OwnerCharacter->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OwnerPawn is not a Character"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerPawn is NULL"));
	}

	// Set Controller
	Controller = Cast<APlayerController>(this);
	if (Controller)
	{
		//UE_LOG(LogTemp, Display, TEXT("Controller: %s"), *Controller->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is NULL"));
	}


	// Bind input
	//Add Input Mapping Context
	
	if (Controller)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem
				= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(KeyboardInputMappingContext, 0);
			}
		}
	}
}

void AKeyboardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKeyboardPlayerController::Move);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AKeyboardPlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AKeyboardPlayerController::StopJump);
	}
}

void AKeyboardPlayerController::Move(const FInputActionValue& Value)
{
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerPawn is NULL, cannot move."));
		return;
	}

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("Move called: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);

	if (Controller)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get camera forward vector
		const FVector ForwardDirection = OwnerPawn->GetActorForwardVector();
		const FVector RightDirection = OwnerPawn->GetActorRightVector();
		//const FVector RightDirection = OwnerPawn->Camera->GetRightVector();

		// add movement 
		OwnerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		OwnerPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
void AKeyboardPlayerController::StartJump()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->Jump();
	}
}

void AKeyboardPlayerController::StopJump()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->StopJumping();
	}
}

void AKeyboardPlayerController::BeginInteraction(const FInputActionValue& Value)
{
	if (OwnerPawn)
	{
		APlayerCharacter* CharacterTemp = Cast<APlayerCharacter>(OwnerPawn);
		if (CharacterTemp)
		{
			CharacterTemp->BeginInteract();
		}
	}
}

void AKeyboardPlayerController::EndInteraction(const FInputActionValue& Value)
{
	if (OwnerPawn)
	{
		APlayerCharacter* CharacterTemp = Cast<APlayerCharacter>(OwnerPawn);
		if (CharacterTemp)
		{
			CharacterTemp->EndInteract();
		}
	}
}
