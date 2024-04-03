#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Interfaces/AnimationAttackInterfece.h"

#include "CharacterPrototype.generated.h"

/********************************************************
*	모든 캐릭터(Player, Monster, NPC)의 베이스 클래스
*	공통적인 요소만을 선언
********************************************************/
UCLASS()
class TEAMNYC_API ACharacterPrototype : public ACharacter, public IAnimationAttackInterfece
{
	GENERATED_BODY()

protected:
	// Body SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> BodyMesh;

public:
	ACharacterPrototype();

protected:
	virtual void BeginPlay() override;

	// Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Dead Section
protected:
	float DeadEventDelayTime{ 5.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();
};
