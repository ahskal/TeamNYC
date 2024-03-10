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

#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMousePlayerController::AMousePlayerController()
{
	UE_LOG(LogTemp, Display, TEXT("==================== MousePlayerController ===================="));

	bShowMouseCursor = true;
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
	// ClickAction
	FString IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Mouse_Click.IA_Mouse_Click'");
	UInputAction* IaClick = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaClick) ClickAction = IaClick;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to load IA_Move: %s"), *IaPath);

	// JumpAction
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Jump.IA_Jump'");
	UInputAction* IaJump = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, *IaPath));
	if (IaJump) JumpAction = IaJump;
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
}

void AMousePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &AMousePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AMousePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Canceled, this, &AMousePlayerController::OnSetDestinationReleased);

		// Setup jump input events
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMousePlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMousePlayerController::StopJump);
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
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
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
