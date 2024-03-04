// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/PlayerAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		PlayerCharacter = Cast<APlayerCharacter>(Pawn);
		PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (PlayerCharacter)
	{
		Velocity = PlayerCharacter->GetVelocity();
		bIsInAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
		//bIsCrouching = PlayerCharacter->GetCharacterMovement()->IsCrouching();
	}
}
