// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterPrototype.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerInteractionComponent;

UCLASS()
class TEAMNYC_API APlayerCharacter : public ACharacterPrototype
{
	GENERATED_BODY()
private:
	// SpringArm
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	UPlayerInteractionComponent* InteractionComponent;
public:
	APlayerCharacter();

	FORCEINLINE UPlayerInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }
	FORCEINLINE void SetInteractionComponent(UPlayerInteractionComponent* InInteractionComponent) { InteractionComponent = InInteractionComponent; }

	void BeginInteract() const;
	void EndInteract() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


};
