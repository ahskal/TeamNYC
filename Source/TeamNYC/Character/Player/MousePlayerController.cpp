// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/MousePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/Player/PlayerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedPlayerInput.h"

#include <Kismet/KismetMathLibrary.h>

#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMousePlayerController::AMousePlayerController()
{
	UE_LOG(LogTemp, Display, TEXT("==================== MousePlayerController ===================="));

	bShowMouseCursor = true;
	bMoveToMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	ShortPressThreshold = 0.3f;


	// Set DMC
	FString DmcPath = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Assets/Input/IMC_Mouse.IMC_Mouse'");
	UInputMappingContext* DmcObj = Cast<UInputMappingContext>(StaticLoadObject(UInputMappingContext::StaticClass(), nullptr, *DmcPath));
	if (DmcObj) MouseInputMappingContext = DmcObj;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load DMC: %s"), *DmcPath);

	// Set IA
	// LeftClickAction
	FString IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Mouse_LClick.IA_Mouse_LClick'");
	UInputAction* IaLClick = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaLClick) LeftClickAction = IaLClick;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_LClick: %s"), *IaPath);

	// RightClickAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Mouse_RClick.IA_Mouse_RClick'");
	UInputAction* IaRClick = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaRClick) RightClickAction = IaRClick;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_RClick: %s"), *IaPath);

	// JumpAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Jump.IA_Jump'");
	UInputAction* IaJump = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaJump) JumpAction = IaJump;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Jump: %s"), *IaPath);

	// InteractionAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Interaction.IA_Interaction'");
	UInputAction* IaInter = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaInter) InteractionAction = IaInter;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Jump: %s"), *IaPath);

	// Set FxCursor
	FString FxCursorPath = TEXT("/Script/Niagara.NiagaraSystem'/Game/Assets/Cursor/FX_Cursor.FX_Cursor'");
	UNiagaraSystem* FxCursorObj = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *FxCursorPath));
	if (FxCursorObj) FxCursor = FxCursorObj;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load FxCursor: %s"), *FxCursorPath);

}

void AMousePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MouseInputMappingContext, 0);
	}

	// Get PlayerPawn->GetController()
	OwnerPawn = Cast<APawn>(GetPawn());
	if (OwnerPawn)
	{
		//UE_LOG(LogTemp, Display, TEXT("OwnerPawn: %s"), *OwnerPawn->GetName());
		OwnerCharacter = Cast<APlayerCharacter>(OwnerPawn);
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
}

void AMousePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup left click input events
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AMousePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Triggered, this, &AMousePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Canceled, this, &AMousePlayerController::OnSetDestinationReleased);

		// Setup right click input events
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AMousePlayerController::Attack);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &AMousePlayerController::Attack);
		//EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnSetDestinationReleased);
		//EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Canceled, this, &AMousePlayerController::OnSetDestinationReleased);

		// Setup jump input events
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMousePlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMousePlayerController::StopJump);

		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMousePlayerController::BeginInteract);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AMousePlayerController::EndInteract);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMousePlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AMousePlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer
	//APawn* ControlledPawn = GetPawn();
	if (OwnerPawn)
	{
		FVector WorldDirection = (CachedDestination - OwnerPawn->GetActorLocation()).GetSafeNormal();
		OwnerPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AMousePlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FxCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void AMousePlayerController::StartJump()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->Jump();
	}
}

void AMousePlayerController::StopJump()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->StopJumping();
	}
}

void AMousePlayerController::BeginInteract()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->BeginInteract();
	}
}

void AMousePlayerController::EndInteract()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->EndInteract();
	}
}

void AMousePlayerController::Attack()
{
	if (OwnerCharacter)
	{
		// stop movement
		StopMovement();

		// Look in the direction you clicked
		// Smooth directional rotation
		FHitResult Hit;
		bool bHitSuccessful = false;
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		if (bHitSuccessful)
		{
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), Hit.Location);
			float RotationSpeed = 12.f;
			OwnerCharacter->SetActorRotation(FMath::RInterpTo(OwnerCharacter->GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed));
		}

		OwnerCharacter->UnarmedAttack();
	}
}
