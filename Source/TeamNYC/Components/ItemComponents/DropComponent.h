#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DropComponent.generated.h"

class UItemBase;

UCLASS(ClassGroup = (Custom))
class TEAMNYC_API UDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDropComponent();

	//UItemBase* InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);		
};
