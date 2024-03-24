// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/PlayerAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		PlayerCharacter = Cast<APlayerCharacter>(Pawn);
		PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
		Movement = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter)
	{
		Velocity = PlayerCharacter->GetVelocity();
		GroundSpeed = Velocity.Size2D();
		bIsMoving = GroundSpeed > MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling && (Velocity.Z > JumpingThreshould);
		//bIsCrouching = PlayerCharacter->GetCharacterMovement()->IsCrouching();
		PlayerState = static_cast<int32>(PlayerCharacter->PlayerState);
	}
}
