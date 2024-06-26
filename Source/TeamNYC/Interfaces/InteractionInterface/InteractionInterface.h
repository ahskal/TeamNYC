// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class APlayerCharacter;

UENUM()
enum class EInteractableType : uint8
{
	// Linetrace Collision TargetType
	Pickup				UMETA(DisplayName = "Pickup"),
	Monster				UMETA(DisplayName = "Monster"),
	NonPlayerCharacter	UMETA(DisplayName = "NonPlayerCharacter"),
	Device				UMETA(DisplayName = "Device"),
	Toggle				UMETA(DisplayName = "Toggle"),
	Container			UMETA(DisplayName = "Container"),
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

	FInteractableData() :
		InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.0f)
	{

	};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;
	UPROPERTY(EditInstanceOnly)
	FText Action;

	// used only for pickup
	UPROPERTY(EditInstanceOnly)
	int32 Quantity;


	// used for things like valves, doors, etc. that require an interaction timer
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class TEAMNYC_API IInteractionInterface
{
	GENERATED_BODY()
public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(APlayerCharacter* PlayerCharacter);

	FInteractableData InteractableData;
};
