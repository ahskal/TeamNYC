
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillData.generated.h"

UENUM()
enum class ETargetType : uint8
{
	Self,
	SelectedEnemy,
	SelectedAlly,
	SelectedArea,
	AreaAroundSelf,
	NontargetProjectile
};


UENUM()
enum class EDamageType : uint8
{
	Pyhsical,
	Fire,
	Cold,
	Lightning,
};