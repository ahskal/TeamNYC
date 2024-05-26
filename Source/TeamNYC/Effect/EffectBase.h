// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "EffectBase.generated.h"

class UNiagaraComponent;

UCLASS()
class TEAMNYC_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> EffectParticle;
};
