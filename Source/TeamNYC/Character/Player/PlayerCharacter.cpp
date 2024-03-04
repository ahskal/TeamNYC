#include "Character/Player/PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

	// SpringArm
	//CppMacro::CreateComponent<USpringArmComponent>(this, SpringArm, TEXT("SpringArm"), GetCapsuleComponent());
	SpringArm = this->CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controlle
	//SpringArm->SetRelativeLocation(FVector(0, 50, 50));
	//SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));

	// Camera
	//CppMacro::CreateComponent<UCameraComponent>(this, Camera, TEXT("Camera"), SpringArm);
	Camera = this->CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

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
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
