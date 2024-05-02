// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"
#include "TestMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API ATestMonster : public ACharacterBase, public IMonsterAIInterface
{
	GENERATED_BODY()
	
public:
		ATestMonster();
	
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

protected:
	virtual void BeginFocus() override;
	virtual void EndFocus() override;

	//====================================================================================
	//  Interface
	//====================================================================================
public:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	FAICharacterAttackFinished OnAttackFinished;
	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	//====================================================================================
	//  Attack Section
	//====================================================================================
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> AttackMontage;

	virtual void ProcessAttack() override;
	virtual void AttackBegin() override;
	virtual void AttackEnd(UAnimMontage* TargetMontage = nullptr, bool bIsProperlyEnded = true) override;
	virtual void NotifyAttackEnd() override;

	//====================================================================================
	//  Dead Section
	//====================================================================================
protected:
	virtual void SetDead() override;
};
