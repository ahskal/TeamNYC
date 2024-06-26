// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerInteractionComponent;
class UInventoryComponent;
class UItemBase;

UENUM(BlueprintType)
enum class EPlayerCurrentState : uint8
{
	NORMAL,
	ATTACKING,
	DEAD
};


UCLASS()
class TEAMNYC_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
friend class AMousePlayerController;
friend class UPlayerAnimInstance;

	//====================================================================================
	//  Character Section
	//====================================================================================
public:
	APlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetMaxWalkSpeed(float InMaxWalkSpeed);
	virtual void SetDead() override;

	//====================================================================================
	//  SkeletalMesh Section
	//====================================================================================
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Face;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Torso;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Legs;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMesh> Feet;


	//====================================================================================
	//  SkeletalMesh Component Section
	//====================================================================================
protected:
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


	//====================================================================================
	//  Camera Section
	//====================================================================================
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

public:
	void SetCameraZoom(float InZoomValue);
	void SetCameraPitch(float InPitchValue);
	void SetCameraYaw(float InYawValue);


	//====================================================================================
	//  UI Widget Section
	//====================================================================================
protected:
	virtual void SetupCharacterWidget(class UExtendedUserWidget* InUserWidget) override;


	//====================================================================================
	//   Interaction Section
	//====================================================================================
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPlayerInteractionComponent> InteractionComponent;

public:
	FORCEINLINE UPlayerInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }
	FORCEINLINE void SetInteractionComponent(UPlayerInteractionComponent* InInteractionComponent) { InteractionComponent = InInteractionComponent; }

	void UpdateInteractionWidget() const;
	void BeginInteract() const;
	void EndInteract() const;

	void ToggleMenu() const;


	//====================================================================================
	//   Inventory Section
	//====================================================================================
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;

public:
	FORCEINLINE UInventoryComponent* GetInventory() const { return InventoryComponent; }
	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);


	//====================================================================================
	//  Player State Section
	//====================================================================================
protected:
	EPlayerCurrentState	PlayerCurrentState;

public:
	FORCEINLINE void SetPlayerState(EPlayerCurrentState InPlayerState) { PlayerCurrentState = InPlayerState; }
	FORCEINLINE EPlayerCurrentState GetPlayerState() const { return PlayerCurrentState; }

	//====================================================================================
	//  Combo Section
	//====================================================================================
protected:
	int32			CurrentCombo{ 0 };
	FTimerHandle    ComboTimerHandle;
	bool			bHasNextComboCommand{ false };


	//====================================================================================
	//  Timer Section
	//====================================================================================
protected:
	virtual void SetComoboCheckTimer();		// 타이머 발동 함수
	virtual void CheckComboInput();			// 타이머 발동시 콤보 입력 체크 함수

	//====================================================================================
	//  Default Attack Section
	//====================================================================================
protected:
	virtual void ProcessAttack() override;

	//====================================================================================
	//  Unarmed Attack Section
	//====================================================================================
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> UnarmedAttackMontage;

	// Unarmed Jab DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerJabDataAsset> UnarmedJabDataAsset;

	void UnarmedAttackBegin();
	void UnarmedAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

	//====================================================================================
	//  Test Section
	//====================================================================================
	void ModifyStat(float value);
};
