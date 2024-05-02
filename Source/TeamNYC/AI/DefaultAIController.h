// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADefaultAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> Blackboardsset;

public:
	void RunAI();
	void StopAI();
};
