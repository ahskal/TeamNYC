// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/AnimNotify_UnarmedAttackHitCheck.h"
#include "Interfaces/CharacterInterface/PlayerInterface/AnimationAttackInterfece.h"

void UAnimNotify_UnarmedAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IAnimationAttackInterfece* AttackCharacter = Cast<IAnimationAttackInterfece>(MeshComp->GetOwner());
		if (AttackCharacter)
		{
			AttackCharacter->AttackHitCheck();
		}
	}
}
