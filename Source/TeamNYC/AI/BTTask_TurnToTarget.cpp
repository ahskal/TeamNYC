// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "AITextMacro.h"
#include "AIController.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
    NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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

	// 블랙보드에서 타겟 키의 값을 가져옴
	//APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIController::TargetKey));
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (!TargetPawn)
	{
		// 타겟이 없으면 실패 리턴
		return EBTNodeResult::Failed;
	}

	// AI 캐릭터의 회전 속도를 가져옴
	float TurnSpeed = AICharacter->GetAITurnSpeed();
	// 타겟을 향하는 회전값 계산
	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	// AI 캐릭터를 회전시킴
	ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));

	return EBTNodeResult::Succeeded;
}
