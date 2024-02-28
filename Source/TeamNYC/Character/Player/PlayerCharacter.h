// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterPrototype.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TEAMNYC_API APlayerCharacter : public ACharacterPrototype
{
	GENERATED_BODY()
	
	
private:
	// SpringArm
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent*	SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent*		Camera;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
