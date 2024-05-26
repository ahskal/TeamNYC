// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/EffectBurning.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Data/DamageType/DamageType_Fire.h"

AEffectBurning::AEffectBurning()
{
	EffectParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EffectParticle"));
	EffectParticle->SetupAttachment(RootComponent);

	// life span
	InitialLifeSpan = 10.0f;
}

void AEffectBurning::BeginPlay()
{
	Super::BeginPlay();

	// 델리게이트 정의 및 바인딩
	FTimerDynamicDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("Burning"));

	// 타이머 설정
	UKismetSystemLibrary::K2_SetTimerDelegate(TimerDelegate, 2.0f, true);
}

void AEffectBurning::Burning()
{
	// 데미지 적용
	float BaseDamage = 10.0f;
	//UGameplayStatics::ApplyDamage(GetOwner(), BaseDamage, nullptr, this, UDamageType_Fire::StaticClass());
	UGameplayStatics::ApplyDamage(GetAttachParentActor(), BaseDamage, nullptr, this, nullptr);


}
