// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterPrototype.generated.h"

UCLASS()
class TEAMNYC_API ACharacterPrototype : public ACharacter
{
	GENERATED_BODY()

protected:
	// SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh{ nullptr };

public:
	// Sets default values for this character's properties
	ACharacterPrototype();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
