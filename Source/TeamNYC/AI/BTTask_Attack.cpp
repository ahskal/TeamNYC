// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// 이 태스크를 실행한 AI 컨트롤러가 소유한 폰을 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	// 폰이 IMonsterAIInterface를 상속받았는지 확인
	IMonsterAIInterface* AICharacter = Cast<IMonsterAIInterface>(ControllingPawn);
	if (!AICharacter)
	{
		// AI 인터페이스가 없으면 실패 리턴
		return EBTNodeResult::Failed;
	}


	// AI 캐릭터에게 공격이 끝났을때 호출할 델리게이트를 설정
	FAICharacterAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);
	AICharacter->SetAIAttackDelegate(OnAttackFinished);

	// 공격 실행
	AICharacter->AttackByAI();
	// 공격 애니메이션이 끝날때까지 공격이 끝난	게 아니므로 InProgress 리턴
	return EBTNodeResult::InProgress;
}
