// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DamageType/DamageType_Fire.h"
#include "Components/StatusEffectComponent.h"

UDamageType_Fire::UDamageType_Fire()
{
}

void UDamageType_Fire::SetOnFire()
{
}

void UDamageType_Fire::TriggerEffect(UStatusEffectComponent* StatusEffectComp)
{
	StatusEffectComp->TriggerEffect(EStatusEffectType::Burning);
}
