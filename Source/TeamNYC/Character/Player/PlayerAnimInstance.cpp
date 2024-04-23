// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/PlayerAnimInstance.h"
#include "Character/CharacterBase.h"
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
		OwnerCharacter = Cast<ACharacterBase>(Pawn);
		//PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
		Movement = OwnerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter)
	{
		Velocity = OwnerCharacter->GetVelocity();
		GroundSpeed = Velocity.Size2D();
		bIsMoving = GroundSpeed > MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling && (Velocity.Z > JumpingThreshould);
		//bIsCrouching = PlayerCharacter->GetCharacterMovement()->IsCrouching();

		// PlayerState
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OwnerCharacter);
		if (PlayerCharacter)
		{
			PlayerState = static_cast<int32>(PlayerCharacter->PlayerCurrentState);
		}
	}
}
