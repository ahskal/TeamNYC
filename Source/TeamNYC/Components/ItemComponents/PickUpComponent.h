#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpComponent.generated.h"

class UItemBase;

UCLASS(ClassGroup=(Item))
class TEAMNYC_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPickUpComponent();

	void InitializePickup(TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);
};
