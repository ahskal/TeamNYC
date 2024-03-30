// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/UnarmedJabAnimNotifyState.h"
#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

FString UUnarmedJabAnimNotifyState::GetNotifyName_Implementation() const
{
	return TEXT("UnarmedJabAnimNotifyState");
}

void UUnarmedJabAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	TObjectPtr<APlayerCharacter> OwnerPlayerCharacter{ Cast<APlayerCharacter>(MeshComp->GetOwner()) };
	if (OwnerPlayerCharacter)
	{
		OwnerPlayerCharacter->SetPlayerState(EPlayerState::ATTACKING);
		//OwnerPlayerCharacter->SetMaxWalkSpeed(0);
		OwnerPlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		OwnerPlayerCharacter->ComboCount %= 2;


	}
}

void UUnarmedJabAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	TObjectPtr<APlayerCharacter> OwnerPlayerCharacter{ Cast<APlayerCharacter>(MeshComp->GetOwner()) };
	if (OwnerPlayerCharacter)
	{
		OwnerPlayerCharacter->SetPlayerState(EPlayerState::NORMAL);
		//OwnerPlayerCharacter->SetMaxWalkSpeed(600);
		OwnerPlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		OwnerPlayerCharacter->ComboCount %= 2;
	}
}
