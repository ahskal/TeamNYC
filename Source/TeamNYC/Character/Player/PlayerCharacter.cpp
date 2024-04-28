// Fill out your copyright notice in the Description page of Project Settings.
// 
#include "Character/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Data Asset
#include "Character/Player/PlayerJabDataAsset.h"

// Component
#include "Components/CharacterStatComponent.h"
#include "Components/ExtendedWidgetComponent.h"
#include "Components/PlayerInteractionComponent.h"
#include "Components/InventoryComponent.h"

// HpBar Widget
#include "UserInterface/ProgressBar/CharacterHealthPointBarWidget.h"
#include "UserInterface/ProgressBar/HeadUpDisplayStatBarWidget.h"


APlayerCharacter::APlayerCharacter()
{
	UE_LOG(LogTemp, Display, TEXT("==================== PlayerCharacter ===================="));

	//====================================================================================
	//  SkeletalMesh Section
	//====================================================================================
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


	//====================================================================================
	//  SkeletalMesh Component Section
	//====================================================================================
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


	//====================================================================================
	//  Actor, Pawn, Character Section
	//====================================================================================
	// Activate tick
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Mesh Setup
	GetMesh()->SetSkeletalMesh(BodyMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -98));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	//====================================================================================
	//  Camera Section
	//====================================================================================
	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	//====================================================================================
	//  Animation Section
	//====================================================================================
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
	//  Unarmed Attack Section
	//====================================================================================
	// Set Player_Jab Montage
	FString MontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Assets/Character/Player/Animations/AM_Player_Jab.AM_Player_Jab'");
	ConstructorHelpers::FObjectFinder<UAnimMontage> UnarmedAttack(*MontagePath);
	if (UnarmedAttack.Succeeded())
	{
		UnarmedAttackMontage = UnarmedAttack.Object;
		UnarmedAttackMontage->RateScale = 1.0f;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Player_Jab Montage: %s"), *MontagePath);
	}

	// Set Player_Jab DataAsset
	FString DataAssetPath = TEXT("/Script/Engine.Blueprint'/Game/Assets/Character/Player/PlayerAction/JabDataAsset.JabDataAsset_C'");
	ConstructorHelpers::FClassFinder<UPlayerJabDataAsset> DataAsset(*DataAssetPath);
	if (DataAsset.Succeeded())
	{
		UnarmedJabDataAsset = DataAsset.Class->GetDefaultObject<UPlayerJabDataAsset>();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Player_Jab DataAsset: %s"), *DataAssetPath);
	}
	
	//====================================================================================
	//  Interaction, Inventory Component Section
	//====================================================================================
	// CreateDefaultSubobject를 통해 컴포넌트를 생성하면, 컴포넌트 내부에는
	// 부모 클래스인 UActorComponent에서 상속받은 OwnerPrivate라는 멤버 변수가 있습니다.
	// 이 OwnerPrivate 변수에는 해당 컴포넌트를 소유하는 액터 객체의 포인터가 할당됩니다.
	// 따라서 컴포넌트는 자동으로 부모 클래스의 주소를 알게 되며, 따로 바인딩을 할 필요가 없습니다.
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetSlotsCapacity(50.f);
	InventoryComponent->SetWeightCapacity(50.f);

	//====================================================================================
	//  Player State Section
	//====================================================================================
	PlayerCurrentState = EPlayerCurrentState::NORMAL;

	//====================================================================================
	//  Temp Test Section
	//====================================================================================
	CharacterStatComp->ModifyDamage(15.f);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::SetDead()
{
	if (PlayerCurrentState == EPlayerCurrentState::DEAD) return;

	SetPlayerState(EPlayerCurrentState::DEAD);
	Super::SetDead();
}

void APlayerCharacter::SetMaxWalkSpeed(float InMaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InMaxWalkSpeed;
}

void APlayerCharacter::SetCameraZoom(float InZoomValue)
{
	float ZoomScale = 10.f;
	InZoomValue *= ZoomScale;

	float MinZoomValue = 200.f;	
	float MaxZoomValue = 800.f;
	float CurrentZoomValue = SpringArm->TargetArmLength;

	SpringArm->TargetArmLength = FMath::Clamp(CurrentZoomValue + InZoomValue, MinZoomValue, MaxZoomValue);
}

void APlayerCharacter::SetCameraPitch(float InPitchValue)
{
	float PitchScale = 5.f;
	InPitchValue *= PitchScale;

	float MinPitchValue = -80.f;
	float MaxPitchValue = 0.f;
	float CurrentPitchValue = SpringArm->GetRelativeRotation().Pitch;

	SpringArm->SetRelativeRotation(FRotator(FMath::Clamp(CurrentPitchValue + InPitchValue, MinPitchValue, MaxPitchValue), 0.f, 0.f));
}

void APlayerCharacter::SetCameraYaw(float InYawValue)
{
	SpringArm->AddRelativeRotation(FRotator(0.0f, InYawValue, 0.0f));
}

void APlayerCharacter::UpdateInteractionWidget() const
{
	InteractionComponent->UpdateInteractionWidget();
}

void APlayerCharacter::BeginInteract() const
{
	InteractionComponent->BeginInteract();
}

void APlayerCharacter::EndInteract() const
{
	InteractionComponent->EndInteract();
}

void APlayerCharacter::ToggleMenu() const
{ 
	InteractionComponent->ToggleMenu();
}

void APlayerCharacter::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	InteractionComponent->DropItem(ItemToDrop, QuantityToDrop);
}

//void APlayerCharacter::UnarmedAttack()
//{
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//	if (AnimInstance && UnarmedAttackMontage)
//	{
//		if (!AnimInstance->Montage_IsPlaying(UnarmedAttackMontage))
//		{
//			FName SectionName{ (ComboCount % 2) ? TEXT("LeftJab") : TEXT("RightJab") };
//
//			AnimInstance->Montage_Play(UnarmedAttackMontage);
//			AnimInstance->Montage_JumpToSection(SectionName, UnarmedAttackMontage);
//
//			ComboCount++;
//		}
//	}
//}

void APlayerCharacter::ProcessAttack()
{
	if (PlayerCurrentState == EPlayerCurrentState::DEAD) return;

	// 콤보가 0인 경우
	if (CurrentCombo == 0)
	{
		// 나중에 무기 공격으로 변경
		UnarmedAttackBegin();
		return;
	}
	// 콤보가 1 이상인 경우
	else
	{


		// 콤보 타이머가 유효한 경우
		if (ComboTimerHandle.IsValid())
		{
			//UE_LOG(LogTemp, Warning, TEXT("2"));
			bHasNextComboCommand = true;
		}
		// 콤보 타이머가 유효하지 않은 경우
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("3"));
			bHasNextComboCommand = false;
		}
	}
}

void APlayerCharacter::UnarmedAttackBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("UnarmedAttackBegin"));
	// 시작 콤보 스테이지 설정
	CurrentCombo = 1;
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	SetPlayerState(EPlayerCurrentState::ATTACKING);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);


	// 애니메이션 실행
	const float AttackSpeed = CharacterStatComp->GetTotalStat().AttackSpeed;
	UE_LOG(LogTemp, Warning, TEXT("AttackSpeed: %f"), AttackSpeed);
	AnimInstance->Montage_Play(UnarmedAttackMontage, AttackSpeed);

	// 애니메이션 종료 델리게이트 설정
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &APlayerCharacter::UnarmedAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, UnarmedAttackMontage);


	// 콤보 타이머 핸들 무효화
	ComboTimerHandle.Invalidate();
	// 콤보 타이머 발동
	SetComoboCheckTimer();
}

void APlayerCharacter::UnarmedAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	UE_LOG(LogTemp, Warning, TEXT("UnarmedAttackEnd"));
	ensure(CurrentCombo != 0);

	CurrentCombo = 0;
	SetPlayerState(EPlayerCurrentState::NORMAL);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APlayerCharacter::SetupCharacterWidget(UExtendedUserWidget* InUserWidget)
{
	Super::SetupCharacterWidget(InUserWidget);

	UCharacterHealthPointBarWidget* HpBarWidget = Cast<UCharacterHealthPointBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetHpBarColor(FLinearColor::Green);
	}

	UHeadUpDisplayStatBarWidget* MainProgressBar = Cast<UHeadUpDisplayStatBarWidget>(InUserWidget);
	if (MainProgressBar)
	{
		switch (MainProgressBar->GetStatType())
		{
		case EStatProgressBarType::Health:
			MainProgressBar->SetMaxValue(CharacterStatComp->GetMaxHealthPoint());
			MainProgressBar->SetCurrentValue(CharacterStatComp->GetCurrentHealthPoint());
			CharacterStatComp->OnHealthPointChanged.AddUObject(MainProgressBar, &UHeadUpDisplayStatBarWidget::SetCurrentValue);
			break;
		case EStatProgressBarType::Mana:
			MainProgressBar->SetMaxValue(CharacterStatComp->GetMaxManaPoint());
			MainProgressBar->SetCurrentValue(CharacterStatComp->GetCurrentManaPoint());
			CharacterStatComp->OnManaPointChanged.AddUObject(MainProgressBar, &UHeadUpDisplayStatBarWidget::SetCurrentValue);
			break;
		case EStatProgressBarType::Experience:
			MainProgressBar->SetMaxValue(CharacterStatComp->GetMaxExperiencePoint());
			MainProgressBar->SetCurrentValue(CharacterStatComp->GetCurrentExperiencePoint());
			CharacterStatComp->OnExperiencePointChanged.AddUObject(MainProgressBar, &UHeadUpDisplayStatBarWidget::SetCurrentValue);
			break;
		default:
			break;
		}

	}
}

void APlayerCharacter::SetComoboCheckTimer()
{
	//UE_LOG(LogTemp, Warning, TEXT("SetComoboCheckTimer"));

	// 배열의 인덱스 체크
	int32 ComboIndex = CurrentCombo - 1;
	ensure(UnarmedJabDataAsset->EffectiveFrameCount.IsValidIndex(ComboIndex));

	// 콤보 타이머 설정
	const float AttackSpeedRate = CharacterStatComp->GetTotalStat().AttackSpeed;
	const float ComboEffectiveTime = (UnarmedJabDataAsset->EffectiveFrameCount[ComboIndex] / UnarmedJabDataAsset->FramePerSceond) / AttackSpeedRate;
	//UE_LOG(LogTemp, Log, TEXT("ComboEffectiveTime: %f"), ComboEffectiveTime);
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APlayerCharacter::CheckComboInput, ComboEffectiveTime, false);
	}
}

void APlayerCharacter::CheckComboInput()
{
	//UE_LOG(LogTemp, Warning, TEXT("CheckComboInput"));

	// 콤보 타이머 핸들 무효화 (추가 발동하지 않도록)
	ComboTimerHandle.Invalidate();

	//UE_LOG(LogTemp, Log, TEXT("bHasNextComboCommand: %d"), bHasNextComboCommand);
	// 다음 콤보가 있는지 체크
	if (bHasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		// 다음 콤보 state 설정
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, UnarmedJabDataAsset->MaxComboCount);
		// 다음 콤보 인덱스 설정
		int32 ComboIndex = CurrentCombo - 1;
		ensure(UnarmedJabDataAsset->MontageSectionNameSuffix.IsValidIndex(ComboIndex));

		// 다음 콤보 이름 설정
		FName NextComboSectionName = *FString::Printf(TEXT("%s%s"), 
			*UnarmedJabDataAsset->MontageSectionNamePrefix,
			*UnarmedJabDataAsset->MontageSectionNameSuffix[ComboIndex]);

		//UE_LOG(LogTemp, Log, TEXT("NextComboSectionName: %s"), *NextComboSectionName.ToString());

		// 다음 콤보 애니메이션 실행
		const float AttackSpeed = CharacterStatComp->GetTotalStat().AttackSpeed;
		AnimInstance->Montage_JumpToSection(NextComboSectionName, UnarmedAttackMontage);

		// 콤보 타이머 재설정
		SetComoboCheckTimer();
		// 입력값 초기화
		bHasNextComboCommand = false;
	}
}

void APlayerCharacter::ModifyStat(float value)
{

	if (value > 0)
	{
		value *= 20;
		CharacterStatComp->Heal(value);
		CharacterStatComp->RestoreMana(value);
	}
	else
	{
		value *= -20;
		CharacterStatComp->ApplyDamage(value);
		CharacterStatComp->ApplyManaCost(value);
	}
}
