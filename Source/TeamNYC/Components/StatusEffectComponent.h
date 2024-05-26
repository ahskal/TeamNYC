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
	UStatusEffectComponent();

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<AActor> BurningEffectClass;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TriggerEffect(EStatusEffectType EffectType);
};
