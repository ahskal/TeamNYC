// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusEffectComponent.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UStatusEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusEffectComponent::TriggerEffect(EStatusEffectType EffectType)
{
	FTransform SpawnTransform = GetOwner()->GetActorTransform();


	switch (EffectType)
	{
	case EStatusEffectType::Burning:
	{
		// Actor Spawn
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(BurningEffectClass, SpawnTransform);

		// Attach the effect to the owner
		SpawnActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	break;
	case EStatusEffectType::Stunned:
		// Do something
		break;
	case EStatusEffectType::Slowed:
		// Do something
		break;
	case EStatusEffectType::Blinded:
		// Do something
		break;
	default:
		break;
	}
}

