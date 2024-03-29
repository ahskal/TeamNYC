#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterPrototype.generated.h"

/********************************************************
*	모든 캐릭터(Player, Monster, NPC)의 베이스 클래스
*	공통적인 요소만을 선언
********************************************************/
UCLASS()
class TEAMNYC_API ACharacterPrototype : public ACharacter
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
};
