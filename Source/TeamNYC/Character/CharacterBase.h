#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Interfaces
#include "Interfaces/CharacterInterface/PlayerInterface/AnimationAttackInterfece.h"
#include "Interfaces/CharacterInterface/CharacterWidgetInterface.h"
#include "Interfaces/InteractionInterface/InteractionInterface.h"

#include "CharacterBase.generated.h"

//====================================================================================
//  모든 캐릭터(Player, Monster, NPC)의 베이스 클래스
//====================================================================================
UCLASS()
class TEAMNYC_API ACharacterBase : public ACharacter, public IAnimationAttackInterfece, public ICharacterWidgetInterface, public IInteractionInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
	
	//====================================================================================
	//  SkeletalMesh
	//====================================================================================
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> BodyMesh;


	//====================================================================================
	//  Character Stat Section
	//====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterStatComponent> CharacterStatComp;


	//====================================================================================
	//  UI Widget Section
	//====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UExtendedWidgetComponent> HpBarWidgetComp;

	virtual void SetupCharacterWidget(class UExtendedUserWidget* InUserWidget) override;


	//====================================================================================
	//  Attack Section
	//====================================================================================
protected:
	virtual void ProcessAttack();
	virtual void AttackBegin();
	virtual void AttackEnd(UAnimMontage* TargetMontage = nullptr, bool bIsProperlyEnded = true);
	virtual void NotifyAttackEnd();

	//====================================================================================
	//  Take a Hit Section
	//====================================================================================
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	//====================================================================================
	//  Dead Section
	//====================================================================================
protected:
	float DeadEventDelayTime{ 5.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();
};
