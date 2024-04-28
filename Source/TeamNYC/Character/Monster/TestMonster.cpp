// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/TestMonster.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/DefaultAIController.h"

// Components
#include "Components/CharacterStatComponent.h"


ATestMonster::ATestMonster()
{
	UE_LOG(LogTemp, Display, TEXT("==================== TestMonster ===================="));

	PrimaryActorTick.bCanEverTick = true;

	// Set AI
	AIControllerClass = ADefaultAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Body SkeletalMesh
	FString MeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Character/MetaHumans/Character/Male/Medium/NormalWeight/Body/m_med_nrw_body.m_med_nrw_body'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(*MeshPath);
	if (ObjectFinder.Succeeded()) BodyMesh = ObjectFinder.Object;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Object: %s"), *MeshPath);

	// Face SkeletalMesh
	MeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Character/MetaHumans/Character/Face/FaceMesh.FaceMesh'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> FaceObjectFinder(*MeshPath);
	if (FaceObjectFinder.Succeeded()) Face = FaceObjectFinder.Object;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Object: %s"), *MeshPath);

	// Mesh Setup
	GetMesh()->SetSkeletalMesh(BodyMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Face Mesh Setup
	FaceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	FaceMesh->SetupAttachment(GetMesh());
	FaceMesh->SetSkeletalMesh(Face);

	// Torso SkeletalMesh
	TorsoMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Torso"));
	TorsoMesh->SetupAttachment(GetMesh());
	TorsoMesh->SetSkeletalMesh(Torso);

	// Legs SkeletalMesh
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	LegsMesh->SetupAttachment(GetMesh());
	LegsMesh->SetSkeletalMesh(Legs);

	// Feet SkeletalMesh
	FeetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
	FeetMesh->SetupAttachment(GetMesh());
	FeetMesh->SetSkeletalMesh(Feet);

	// Set Body AnimClass
	FString AnimBpPath = TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/Characters/Player/ABP_Player.ABP_Player_C'");
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimBpClass(*AnimBpPath);
	if (AnimBpClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBpClass.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Body AnimBPClass"));
	}

	// Set Face AnimClass
	FString FaceAnimBpPath = TEXT("/Script/Engine.AnimBlueprint'/Game/Assets/Character/MetaHumans/Common/Face/Face_AnimBP.Face_AnimBP_C'");
	ConstructorHelpers::FClassFinder<UAnimInstance> FaceAnimBpClass(*FaceAnimBpPath);
	if (FaceAnimBpClass.Succeeded())
	{
		FaceMesh->SetAnimInstanceClass(FaceAnimBpClass.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Face AnimBPClass"));
	}

	//====================================================================================
	//  Attack Section
	//====================================================================================
	// 임시
	FString MontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Assets/Character/Player/Animations/AM_Player_Jab.AM_Player_Jab'");
	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackRef(*MontagePath);
	if (AttackRef.Succeeded())
	{
		AttackMontage = AttackRef.Object;
		AttackMontage->RateScale = 1.0f;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Player_Jab Montage: %s"), *MontagePath);
	}

	InteractableData.InteractableType = EInteractableType::Monster;
}

void ATestMonster::SetDead()
{
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DeadTimerHandle,
		FTimerDelegate::CreateLambda(
			[&]()
			{
				Destroy();
			}
		),
		DeadEventDelayTime, false
	);

	// Stop AI
	ADefaultAIController* AIController = Cast<ADefaultAIController>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}

	Super::SetDead();
}

void ATestMonster::BeginFocus()
{
	GetMesh()->SetRenderCustomDepth(true);
	FaceMesh->SetRenderCustomDepth(true);
}

void ATestMonster::EndFocus()
{
	GetMesh()->SetRenderCustomDepth(false);
	FaceMesh->SetRenderCustomDepth(false);
}

float ATestMonster::GetAIPatrolRadius()
{
	return 800.0f;
}

float ATestMonster::GetAIDetectRange()
{
	return 400.0f;
}

float ATestMonster::GetAIAttackRange()
{
	return 100.0f;
}

float ATestMonster::GetAITurnSpeed()
{
	return 2.0f;
}

void ATestMonster::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ATestMonster::AttackByAI()
{

	ProcessAttack();
}

void ATestMonster::ProcessAttack()
{
	AttackBegin();
}

void ATestMonster::AttackBegin()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	// 애니메이션 실행
	const float AttackSpeed = CharacterStatComp->GetTotalStat().AttackSpeed;
	UE_LOG(LogTemp, Warning, TEXT("AttackSpeed: %f"), AttackSpeed);
	AnimInstance->Montage_Play(AttackMontage, AttackSpeed);

	// 애니메이션 종료 델리게이트 설정
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ATestMonster::AttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
}

void ATestMonster::AttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	Super::AttackEnd();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ATestMonster::NotifyAttackEnd()
{
	Super::NotifyAttackEnd();

	OnAttackFinished.ExecuteIfBound();
}
