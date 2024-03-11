#include "Character/Player/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Character/Player/Component/PlayerInteractionComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Skeletal Mesh
	FString MeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Character/Player/sk_CharM_Base.sk_CharM_Base'");
	//CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, MeshPath);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(*MeshPath);
	if (ObjectFinder.Succeeded()) SkeletalMesh = ObjectFinder.Object;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Object: %s"), *MeshPath);

	// Mesh Setup
	GetMesh()->SetSkeletalMesh(SkeletalMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));

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

	// CreateDefaultSubobject�� ���� ������Ʈ�� �����ϸ�, ������Ʈ ���ο���
	// �θ� Ŭ������ UActorComponent���� ��ӹ��� OwnerPrivate��� ��� ������ �ֽ��ϴ�.
	// �� OwnerPrivate �������� �ش� ������Ʈ�� �����ϴ� ���� ��ü�� �����Ͱ� �Ҵ�˴ϴ�.
	// ���� ������Ʈ�� �ڵ����� �θ� Ŭ������ �ּҸ� �˰� �Ǹ�, ���� ���ε��� �� �ʿ䰡 �����ϴ�.
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

