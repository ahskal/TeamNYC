// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UnarmedJabAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API UUnarmedJabAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
	public:
		virtual FString GetNotifyName_Implementation() const override;
		virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
		virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
