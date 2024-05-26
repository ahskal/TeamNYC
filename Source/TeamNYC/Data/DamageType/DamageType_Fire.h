// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/Damage/DamageTypeInterface.h"
#include "DamageType_Fire.generated.h"


/**
 * 
 */
UCLASS()
class TEAMNYC_API UDamageType_Fire : public UDamageType, public IDamageTypeInterface
{
	GENERATED_BODY()
	
public:
	UDamageType_Fire();

	void SetOnFire();

	virtual void TriggerEffect(class UStatusEffectComponent* StatusEffectComp) override;
};
