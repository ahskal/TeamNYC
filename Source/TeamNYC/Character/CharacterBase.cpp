// Fill out your copyright notice in the Description page of Project Settings.

// default includes
#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Components/ProgressBar.h>

// component
#include "Components/ExtendedWidgetComponent.h"
#include "Components/CharacterStatComponent.h"

// widget
#include "UserInterface/ProgressBar/CharacterHealthPointBarWidget.h"

#include "Engine/DamageEvents.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	UE_LOG(LogTemp, Display, TEXT("==================== CharacterBase ===================="));

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterCapsule"));

	// Stat Component
	CharacterStatComp = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));

	// Widget Component
	HpBarWidgetComp = CreateDefaultSubobject<UExtendedWidgetComponent>(TEXT("Widget"));
	HpBarWidgetComp->SetupAttachment(GetMesh());
	HpBarWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	FString HpbarWidgetBlueBlueprintPath= TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Characters/UI/WBP_CharacterHpBar.WBP_CharacterHpBar_C'");
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
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Delegate Bindings for Death Event
	CharacterStatComp->OnHealthPointIsZero.AddUObject(this, &ACharacterBase::SetDead);
}

void ACharacterBase::AttackHitCheck()
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

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStatComp->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void ACharacterBase::SetupCharacterWidget(UExtendedUserWidget* InUserWidget)
{
	UCharacterHealthPointBarWidget* HpBarWidget = Cast<UCharacterHealthPointBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(CharacterStatComp->GetMaxHealthPoint());
		HpBarWidget->UpdateHpBar(CharacterStatComp->GetCurrentHealthPoint());
		HpBarWidget->SetHpBarColor(FLinearColor::Red);

		CharacterStatComp->OnHealthPointChanged.AddUObject(HpBarWidget, &UCharacterHealthPointBarWidget::UpdateHpBar);
	}
}

void ACharacterBase::SetDead()
{
	GetCharacterMovement()->DisableMovement();
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HpBarWidgetComp->SetHiddenInGame(true);
}

void ACharacterBase::PlayDeadAnimation()
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
