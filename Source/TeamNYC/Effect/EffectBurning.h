// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/EffectBase.h"
#include "EffectBurning.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API AEffectBurning : public AEffectBase
{
	GENERATED_BODY()
	
public:
	AEffectBurning();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Burning();
};
