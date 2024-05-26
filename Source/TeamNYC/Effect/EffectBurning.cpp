// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/EffectBurning.h"

AEffectBurning::AEffectBurning()
{
	// niagara system
	EffectParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EffectParticle"));
	EffectParticle->SetupAttachment(RootComponent);

}
