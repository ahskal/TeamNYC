// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComponent.generated.h"

UENUM()
enum class EStatusEffectType : uint8
{
	Burning,
	Stunned,
	Slowed,
	Blinded
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMNYC_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	void TriggerEffect(EStatusEffectType EffectType);
};
