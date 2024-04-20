// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterPrototype.h"
#include "Data/PlayerStat.h"
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

	//====================================================================================
	//  Character Section
	//====================================================================================
public:
	APlayerCharacter();
	void SetMaxWalkSpeed(float InMaxWalkSpeed);


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


	//====================================================================================
	//  Player State Section
	//====================================================================================
protected:
	EPlayerState	PlayerCurrentState;

public:
	FORCEINLINE void SetPlayerState(EPlayerState InPlayerState) { PlayerCurrentState = InPlayerState; }
	FORCEINLINE EPlayerState GetPlayerState() const { return PlayerCurrentState; }


	//====================================================================================
	//  Unarmed Attack Section
	//====================================================================================
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> UnarmedAttackMontage;

	// Unarmed Jab DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerJabDataAsset> UnarmedJabDataAsset;

	void ProcessUnarmedAttack();
	void UnarmedAttackBegin();
	void UnarmedAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);


	//====================================================================================
	//  Combo Section
	//====================================================================================
public:
	int32			CurrentCombo{ 0 };
	FTimerHandle    ComboTimerHandle;
	bool			bHasNextComboCommand{ false };


	//====================================================================================
	//  Timer Section
	//====================================================================================
private:
	void SetComoboCheckTimer();		// 타이머 발동 함수
	void CheckComboInput();			// 타이머 발동시 콤보 입력 체크 함수

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	//====================================================================================
	//  Test Section
	//====================================================================================
public:
	TMap<EStatEnum, FStatData> PlayerStatMap;

	FStatData& GetPlayerStat(EStatEnum InStatEnum);
	void SetPlayerStat(EStatEnum InStatEnum, FStatData InStatData);
	void SetUpStatBar();
};
