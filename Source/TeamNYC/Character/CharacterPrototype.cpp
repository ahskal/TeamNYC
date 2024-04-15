// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPrototype.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/UI/ExtendedWidgetComponent.h"
#include "Character/UI/HpBarUserWidget.h"
#include "Component/CharacterStatComponent.h"
#include "Engine/DamageEvents.h"
#include <Components/ProgressBar.h>

// Sets default values
ACharacterPrototype::ACharacterPrototype()
{
	UE_LOG(LogTemp, Display, TEXT("==================== CharacterPrototype ===================="));

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterCapsule"));

	// Stat Component
	CharacterStatComp = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));

	// Widget Component
	HpBarWidgetComp = CreateDefaultSubobject<UExtendedWidgetComponent>(TEXT("Widget"));
	HpBarWidgetComp->SetupAttachment(GetMesh());
	HpBarWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	FString HpbarWidgetBlueBlueprintPath= TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Characters/UI/WBP_HpBar.WBP_HpBar_C'");
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetCompWidgetClass(*HpbarWidgetBlueBlueprintPath);
	if (HpBarWidgetCompWidgetClass.Succeeded())
	{

		HpBarWidgetComp->SetWidgetClass(HpBarWidgetCompWidgetClass.Class);
		HpBarWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarWidgetComp->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBarWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load HP bar widget class."));
	}


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

	// Delegate Bindings for Death Event
	CharacterStatComp->OnHpIsZero.AddUObject(this, &ACharacterPrototype::SetDead);
}

void ACharacterPrototype::AttackHitCheck()
{
	const float AttackRange = CharacterStatComp->GetTotalStat().AttackRange;
	const float AttackRadius = 50.0f; // 임시값, 스탯에 공격범위 추가시 변경할 예정
	const float AttackDamage = CharacterStatComp->GetTotalStat().Damage;

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

	CharacterStatComp->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void ACharacterPrototype::SetupCharacterWidget(UExtendedUserWidget* InUserWidget)
{
	UHpBarUserWidget* HpBarWidget = Cast<UHpBarUserWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(CharacterStatComp->GetMaxHp());
		HpBarWidget->UpdateHpBar(CharacterStatComp->GetCurrentHp());
		HpBarWidget->SetHpBarColor(FLinearColor::Red);

		CharacterStatComp->OnHpChanged.AddUObject(HpBarWidget, &UHpBarUserWidget::UpdateHpBar);
	}
}

void ACharacterPrototype::SetDead()
{
	GetCharacterMovement()->DisableMovement();
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HpBarWidgetComp->SetHiddenInGame(true);
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
