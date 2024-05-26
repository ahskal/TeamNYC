// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageType_Fire.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API UDamageType_Fire : public UDamageType
{
	GENERATED_BODY()
	
public:
	UDamageType_Fire();

	void SetOnFire();
};
