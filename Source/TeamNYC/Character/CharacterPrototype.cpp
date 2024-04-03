// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPrototype.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ACharacterPrototype::ACharacterPrototype()
{
	UE_LOG(LogTemp, Display, TEXT("==================== CharacterPrototype ===================="));

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterCapsule"));

	// 피격 판정 후 Dead montage 테스트용으로 차후 삭제 예정
	// Dead Montage
	FString DeadMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Assets/Character/Player/Animations/AM_Player_Dying.AM_Player_Dying'");
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(*DeadMontagePath);
	if (DeadMontageRef.Succeeded())
	{
		DeadMontage = DeadMontageRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load dead montage asset."));
	}
}

// Called when the game starts or when spawned
void ACharacterPrototype::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterPrototype::AttackHitCheck()
{
	const float AttackRange = 50.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 10.0f;

	const FVector TraceStart = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector TraceEnd = TraceStart + GetActorForwardVector() * AttackRange;

	FHitResult OutHitResult;
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(Attack), false, this);

	bool bHitDetected = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		CollisionQueryParams
	);

	if (bHitDetected)
	{
		//FDamageEvent DamageEvent;
		//OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

		AActor* HitActor = OutHitResult.GetActor();
		if (HitActor)
		{
			FDamageEvent DamageEvent;
			HitActor->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = TraceStart + (TraceEnd - TraceStart) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 2.0f);
#endif
}

float ACharacterPrototype::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;
}

void ACharacterPrototype::SetDead()
{
	GetCharacterMovement()->DisableMovement();
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void ACharacterPrototype::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		if (DeadMontage)
		{
			AnimInstance->Montage_Play(DeadMontage, 1.0f);
		}
	}
}
