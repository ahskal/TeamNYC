// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AITextMacro.h"
#include "AIController.h"
#include "Interfaces/CharacterInterface/MonsterInterface/MonsterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");

	// Detect 간격
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// BT를 소유한 컴포넌트->를 소유한 오너->가 어떤 폰을 빙의하고 있다면
	// 이 태스크를 실행한 AI 컨트롤러가 소유한 폰을 가져옴
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControllingPawn)
	{
		// 유효한 Pawn이 없으면 실패 리턴
		return;
	}

	// 폰이 속한 월드를 가져옴
	UWorld* World = ControllingPawn->GetWorld();
	if (!World)
	{
		// 유효한 월드가 없으면 실패 리턴
		return;
	}

	// 폰의 위치를 가져옴
	FVector Center = ControllingPawn->GetActorLocation();

	// 폰이 IMonsterAIInterface를 상속받았는지 확인
	IMonsterAIInterface* AICharacter = Cast<IMonsterAIInterface>(ControllingPawn);
	if (!AICharacter)
	{
		// AI 인터페이스가 없으면 실패 리턴
		return;
	}
	// AICharacter의 탐지 반경을 가져옴
	float DetectRadius = AICharacter->GetAIDetectRange();

	// 검출결과를 저장할 배열
	TArray<FOverlapResult> OverlapsResults;
	// 쿼리 파라미터
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	// 탐지 반경 내에 있는 캐릭터를 검출
	bool bResult = World->OverlapMultiByChannel(
		OverlapsResults,							// 결과를 저장할 배열
		Center,										// 검출할 위치	
		FQuat::Identity,							// 회전값
		ECC_GameTraceChannel1,						// 채널
		FCollisionShape::MakeSphere(DetectRadius),	// 검출할 형태
		CollisionQueryParam							// 쿼리 파라미터
	);

	// 
	if (bResult)
	{
		// 감지된 모든 결과를 순회하면서
		for (auto const& Overlap : OverlapsResults)
		{
			// Overlap 객체를 폰으로 캐스팅
			auto* Pawn = Cast<APawn>(Overlap.GetActor());
			// 대상이 폰이고, 그 폰이 플레이어 컨트롤러를 가지고 있다면
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				// 블랙보드 컴포넌트의 "Target" 키에 Pawn을 저장
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				// 디버그 스피어를 그림
				// DrawDebugSphere(그릴 월드, 중심 위치, 반지름, 세그먼트 수, 색상, persistent, 지속시간)
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				// 플레이어와의 위치를 점과 선으로 표시
				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Blue, false, 0.2f);
				DrawDebugLine(World, Center, Pawn->GetActorLocation(), FColor::Blue, false, 0.27f);
				return;
			}
		}
	}

	// 플레이어가 탐지되지 않았다면 블랙보드 컴포넌트의 "Target" 키에 nullptr을 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	// 디버그 스피어를 그림 (Red)
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
