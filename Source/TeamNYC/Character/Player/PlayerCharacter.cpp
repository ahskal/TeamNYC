#include "Character/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Character/Player/Component/PlayerInteractionComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

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

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Set AnimClass
	FString AnimBpPath = TEXT("/Game/Blueprints/Characters/Player/ABP_Player.ABP_Player_C");
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimBpClass(*AnimBpPath);
	if (AnimBpClass.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimBpClass.Class);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get AnimBPClass"));
	}

	// CreateDefaultSubobject를 통해 컴포넌트를 생성하면, 컴포넌트 내부에는
	// 부모 클래스인 UActorComponent에서 상속받은 OwnerPrivate라는 멤버 변수가 있습니다.
	// 이 OwnerPrivate 변수에는 해당 컴포넌트를 소유하는 액터 객체의 포인터가 할당됩니다.
	// 따라서 컴포넌트는 자동으로 부모 클래스의 주소를 알게 되며, 따로 바인딩을 할 필요가 없습니다.
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));
}

void APlayerCharacter::BeginInteract() const
{
	InteractionComponent->BeginInteract();
}

void APlayerCharacter::EndInteract() const
{
	InteractionComponent->EndInteract();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

