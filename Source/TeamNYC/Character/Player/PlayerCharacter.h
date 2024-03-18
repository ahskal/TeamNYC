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

protected:
	// Face SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Face;

	// Torso SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Torso;

	// Legs SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Legs;

	// Feet SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Feet;

	// Face SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> FaceMesh;

	// Torso SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> TorsoMesh;

	// Legs SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> LegsMesh;

	// Feet SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> FeetMesh;

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
