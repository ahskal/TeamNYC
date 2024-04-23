// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtendedUserWidget.generated.h"

UCLASS()
class TEAMNYC_API UExtendedUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }
	FORCEINLINE AActor* GetOwningActor() const { return OwningActor; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
};
