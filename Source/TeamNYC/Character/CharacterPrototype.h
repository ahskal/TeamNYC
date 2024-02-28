#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterPrototype.generated.h"

/********************************************************
*	��� ĳ����(Player, Monster, NPC)�� ���̽� Ŭ����
*	�������� ��Ҹ��� ����
********************************************************/
UCLASS()
class TEAMNYC_API ACharacterPrototype : public ACharacter
{
	GENERATED_BODY()

protected:
	// SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh{ nullptr };

public:
	ACharacterPrototype();

protected:
	virtual void BeginPlay() override;
};
