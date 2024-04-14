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

	/*
		객체 로드 방식 변경 (나중에 삭제할 주석)
		기존: UInputMappingContext* DmcObj = Cast<UInputMappingContext>(StaticLoadObject(UInputMappingContext::StaticClass(), nullptr, *ImcPath));
		변경: ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(*ImcPath);

					ConstructorHelpers::FObjectFinder				StaticLoadObject
		설명			생성자에서 객체를 로드하는 방식					게임 실행 중에 동적으로 객체를 로드하는 방식
		장점			간단하고 안전함(생성자에서 한 번에 처리 가능)		실행 중에 동적으로 객체 로드 가능(유연성이 높음)
		단점			실행 중에 동적으로 객체를 로드할 수 없음			코드가 약간 복잡함, 메모리 관리 필요
		사용시기		게임 시작 시 필요한 객체를 로드할 때				게임 실행 중에 동적으로 객체가 필요할 때
		예시			플레이어 입력 매핑 컨텍스트 설정					실행 중에 다른 입력 매핑 컨텍스트 로드
	*/
	// Set DMC
	FString ImcPath = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Assets/Input/IMC_Mouse.IMC_Mouse'");
	ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(*ImcPath);
	if (InputMappingContextRef.Succeeded()) MouseInputMappingContext = InputMappingContextRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load DMC: %s"), *ImcPath);

	// Set IA
	// LeftClick Action
	FString IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Mouse_LClick.IA_Mouse_LClick'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaLeftRef(*IaPath);
	if (IaLeftRef.Succeeded()) LeftClickAction = IaLeftRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_LClick: %s"), *IaPath);

	// RightClick Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Mouse_RClick.IA_Mouse_RClick'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaRightRef(*IaPath);
	if (IaRightRef.Succeeded()) RightClickAction = IaRightRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_RClick: %s"), *IaPath);

	// Camera Zoom Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_CameraZoom.IA_CameraZoom'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaCameraZoomActionRef(*IaPath);
	if (IaCameraZoomActionRef.Succeeded()) CameraZoomAction = IaCameraZoomActionRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_Look: %s"), *IaPath);

	// Camera Rotation Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_CameraRotation.IA_CameraRotation'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaCameraRotationRef(*IaPath);
	if (IaCameraRotationRef.Succeeded()) CameraRotationAction = IaCameraRotationRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_CameraRotation: %s"), *IaPath);

	// Jump Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Jump.IA_Jump'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaJumpRef(*IaPath);
	if (IaJumpRef.Succeeded()) JumpAction = IaJumpRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_Jump: %s"), *IaPath);

	// Interaction Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Interaction.IA_Interaction'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaInterRef(*IaPath);
	if (IaInterRef.Succeeded()) InteractionAction = IaInterRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_Inter: %s"), *IaPath);

	// Inventory Action
	IaPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Assets/Input/IA_Inventory.IA_Inventory'");
	ConstructorHelpers::FObjectFinder<UInputAction> IaInventoryRef(*IaPath);
	if (IaInventoryRef.Succeeded()) InventoryAction = IaInventoryRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load IA_Inventory: %s"), *IaPath);

	// Set FxCursor
	FString FxCursorPath = TEXT("/Script/Niagara.NiagaraSystem'/Game/Assets/Cursor/FX_Cursor.FX_Cursor'");
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> FxCursorRef(*FxCursorPath);
	if (FxCursorRef.Succeeded()) FxCursor = FxCursorRef.Object;
	else UE_LOG(LogTemp, Error, TEXT("Failed to load FxCursor: %s"), *FxCursorPath);

}

void AMousePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Set Input Mode
	//FInputModeGameAndUI InputMode;
	//SetInputMode(InputMode);
	//bShowMouseCursor = true;

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
		// Left Mouse Btn Click
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AMousePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Triggered, this, &AMousePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Canceled, this, &AMousePlayerController::OnSetDestinationReleased);

		// Right Mouse Btn Click
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AMousePlayerController::Attack);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &AMousePlayerController::Attack);
		//EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnSetDestinationReleased);
		//EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Canceled, this, &AMousePlayerController::OnSetDestinationReleased);

		// Camera Zoom
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Started, this, &AMousePlayerController::CameraZoom);
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AMousePlayerController::CameraZoom);

		// Camera Rotation
		EnhancedInputComponent->BindAction(CameraRotationAction, ETriggerEvent::Started, this, &AMousePlayerController::CameraRotate);
		EnhancedInputComponent->BindAction(CameraRotationAction, ETriggerEvent::Triggered, this, &AMousePlayerController::CameraRotate);

		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMousePlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMousePlayerController::StopJump);

		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMousePlayerController::BeginInteract);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AMousePlayerController::EndInteract);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMousePlayerController::ToggleMenu);
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

void AMousePlayerController::CameraZoom(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("CameraZoom"));

	// get owner AController
	if (OwnerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("CameraZoom value: %f"), Value.Get<float>());
		OwnerCharacter->SetCameraZoom(Value.Get<float>());
	}
}

void AMousePlayerController::CameraRotate(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("CameraRotate"));

	// get owner AController
	if (OwnerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("CameraRotate vlaue :%f"), Value.Get<float>());

		OwnerCharacter->SetCameraYaw(Value.Get<float>());
	}
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
void AMousePlayerController::ToggleMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleMenu Key binding"));
	if (OwnerCharacter)
	{
		OwnerCharacter->ToggleMenu();
	}
}


void AMousePlayerController::Attack()
{
	if (OwnerCharacter)
	{
		// 캐릭터 움직임 정지
		StopMovement();

		// 충돌 정보를 저장할 변수
		FHitResult Hit;
		bool bHitSuccessful = false;

		// 마우스 커서에서 lay를 쏘아 충돌 확인
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		if (bHitSuccessful)	// 충돌이 발생했을 경우
		{
			// 바라보는 방향의 계산, yaw만 구함. pitch/roll은 유지.
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), Hit.Location);
			LookAtRotation.Pitch = OwnerCharacter->GetActorRotation().Pitch;
			LookAtRotation.Roll = OwnerCharacter->GetActorRotation().Roll;
			float RotationSpeed = 12.f;

			// 캐릭터 회전을 부드럽게 보간하여 처리
			OwnerCharacter->SetActorRotation(FMath::RInterpTo(OwnerCharacter->GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed));
		}

		// 나중에 이부분은 맵핑된 함수를 호출하게 수정할 예정
		OwnerCharacter->ProcessUnarmedAttack();
	}
}

void AMousePlayerController::OnWheelAction(const FInputActionValue& Value)
{
	if (OwnerCharacter)
	{
		// Get the value of the wheel action
		float WheelValue = Value.Get<float>();

		// Zoom in/out
		OwnerCharacter->SetCameraZoom(WheelValue);
	}
}