// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DefaultAIController.h"
#include "AITextMacro.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ADefaultAIController::ADefaultAIController()
{
	// Set Blackboard Asset
	FString BBAssetPath = TEXT("/Script/AIModule.BlackboardData'/Game/Assets/AI/BB_Monster.BB_Monster'");
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(*BBAssetPath);
	if (BBAssetRef.Succeeded())
	{
		Blackboardsset = BBAssetRef.Object;
	}

	// Set Behavior Tree Asset
	FString BTAssetPath = TEXT("/Script/AIModule.BehaviorTree'/Game/Assets/AI/BT_Monster.BT_Monster'");
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(*BTAssetPath);
	if (BTAssetRef.Succeeded())
	{
		BehaviorTreeAsset = BTAssetRef.Object;
	}
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ADefaultAIController::RunAI()
{
	// Get BlackboardComponent
	//UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();

	// BlackboardAsset과 BlackboardComponent를 사용할 수 있다면
	if (UseBlackboard(Blackboardsset, BlackboardComponent))
	{
		// "HomePos" 키에 폰의 위치를 벡터 값으로 저장
		// 블랙보드에 HomePos 값 설정
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		// BehaviorTree를 실행하고 결과를 RunResult에 저장
		bool RunResult = RunBehaviorTree(BehaviorTreeAsset);
		ensure(RunResult); // 실행결과 확인
	}
}

void ADefaultAIController::StopAI()
{
	// Get Behavior Tree Component
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	// Behavior Tree Component가 유효하다면
	if (BehaviorTreeComponent)
	{
		// Stop Behavior Tree
		BehaviorTreeComponent->StopTree();
	}
}
