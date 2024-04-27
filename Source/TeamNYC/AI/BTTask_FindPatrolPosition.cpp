// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolPosition.h"
#include "AITextMacro.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"

UBTTask_FindPatrolPosition::UBTTask_FindPatrolPosition()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)\
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// BT를 소유한 컴포넌트->를 소유한 오너->가 어떤 폰을 빙의하고 있다면
	// 이 태스크를 실행한 AI 컨트롤러가 소유한 폰을 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn)
	{
		// 유효한 Pawn이 없으면 실패 리턴
		return EBTNodeResult::Failed;
	}

	// 폰이 속한 월드의 내비게이션 시스템을 가져옴 (V1은 버전업된 시스템)
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (!NavSystem)
	{
		// 유효한 네비게이션 시스템이 없으면 실패 리턴
		return EBTNodeResult::Failed;
	}

	// 폰이 IMonsterAIInterface를 상속받았는지 확인
	IMonsterAIInterface* AICharacter = Cast<IMonsterAIInterface>(ControllingPawn);
	if (!AICharacter)
	{
		 //AI 인터페이스가 없으면 실패 리턴
		return EBTNodeResult::Failed;
	}

	// 블랙보드 컴포넌트의 "HomePos" 키에 저장된 값을 가져와서 Origin에 저장
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
	// AI 캐릭터의 순찰 반경을 가져와서 PatrolRadius에 저장
	float PatrolRadius = AICharacter->GetAIPatrolRadius();
	// 다음 순찰 지점을 저장할 변수
	FNavLocation NextPatrolPos;

	// 네비게이션 시스템에서 랜덤한 위치를 가져와서 NextPatrolPos에 저장
	// GetRandomPointInNavigableRadius(기준위치, 반지름, 결과위치)
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolRadius, NextPatrolPos))
	{
		// 블랙보드 컴포넌트의 "PatrolPos" 키에 NextPatrolPos의 위치를 저장
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
		// 태스크 성공 리턴
		return EBTNodeResult::Succeeded;
	}

	// 이전 조건을 하나라도 만족하지 못했다면 태스크 실패 리턴
	return EBTNodeResult::Failed;
}
