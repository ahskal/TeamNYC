// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_AttackInRange.h"
#include "AITextMacro.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("Can Attack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// 이 태스크를 실행한 AI 컨트롤러가 소유한 폰을 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn)
	{
		return false;
	}

	// 폰이 IMonsterAIInterface를 상속받았는지 확인
	IMonsterAIInterface* AICharacter = Cast<IMonsterAIInterface>(ControllingPawn);
	if (!AICharacter)
	{
		// AI 인터페이스가 없으면 실패 리턴
		return false;
	}

	// 타겟을 가져옴
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (!Target)
	{
		return false;
	}

	// 폰과 타겟 사이의 거리를 계산
	//float DistanceToTarget = FVector::Distance(ControllingPawn->GetActorLocation(), Target->GetActorLocation());
	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);

	// 폰의 공격 범위를 가져옴
	float AttackRange = AICharacter->GetAIAttackRange();
	// 폰의 공격범위 안에 타겟이 있는지 확인
	bool bResult = DistanceToTarget <= AttackRange;

	// 결과 리턴
	return bResult;
}
