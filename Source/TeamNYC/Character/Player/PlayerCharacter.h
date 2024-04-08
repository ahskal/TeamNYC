// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterPrototype.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerInteractionComponent;
class UInventoryComponent;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	NORMAL,
	ATTACKING
};


UCLASS()
class TEAMNYC_API APlayerCharacter : public ACharacterPrototype
{
	GENERATED_BODY()
	
friend class AMousePlayerController;
friend class UPlayerAnimInstance;

private:
	// SpringArm
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	// Camera
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	// Interaction Component;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPlayerInteractionComponent> InteractionComponent;

	// Inventory Component;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	// UnarmedAttackMontage
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> UnarmedAttackMontage;

	// Unarmed Jab DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerJabDataAsset> UnarmedJabDataAsset;

	EPlayerState	PlayerCurrentState;

protected:
	// Face SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Face;

	// Torso SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Torso;

	// Legs SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Legs;

	// Feet SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Feet;

	// Face SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> FaceMesh;

	// Torso SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> TorsoMesh;

	// Legs SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> LegsMesh;

	// Feet SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> FeetMesh;
	
// UI Widget Section
protected:
	virtual void SetupCharacterWidget(class UExtendedUserWidget* InUserWidget) override;

public:
	// Combo Section
	int32			CurrentCombo{ 0 };
	FTimerHandle    ComboTimerHandle;
	bool			bHasNextComboCommand{ false };

private:
	// Timer Section
	void SetComoboCheckTimer();		// 타이머 발동 함수
	void CheckComboInput();			// 타이머 발동시 콤보 입력 체크 함수

	// Unarmed Attack Section
	void ProcessUnarmedAttack();	
	void UnarmedAttackBegin();		// UnarmedAttackMontage가 시작될 때 호출되는 함수
	void UnarmedAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);	// UnarmedAttackMontage가 완전히 끝났을 때 호출되는 함수


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	APlayerCharacter();

	FORCEINLINE void SetPlayerState(EPlayerState InPlayerState) { PlayerCurrentState = InPlayerState; }
	FORCEINLINE EPlayerState GetPlayerState() const { return PlayerCurrentState; }
	void SetMaxWalkSpeed(float InMaxWalkSpeed);

	// Camera Section
	void SetCameraZoom(float InZoomValue);
	void SetCameraPitch(float InPitchValue);

	// Get InteractionComponent
	FORCEINLINE UPlayerInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }
	FORCEINLINE void SetInteractionComponent(UPlayerInteractionComponent* InInteractionComponent) { InteractionComponent = InInteractionComponent; }

	// Get InventoryComponent
	FORCEINLINE UInventoryComponent* GetInventory() const { return InventoryComponent; }

	// Interaction function
	void UpdateInteractionWidget() const;
	void BeginInteract() const;
	void EndInteract() const;

	void ToggleMenu() const;
};
