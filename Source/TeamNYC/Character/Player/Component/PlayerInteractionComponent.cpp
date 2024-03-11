// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/PlayerInteractionComponent.h"

#include "GameFramework/Character.h"

#include "Interfaces/InteractionInterface.h"
#include "Character/Player/PlayerCharacter.h"
#include "UserInterface/PlayerHUD.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractionCheckFrequency = 0.1f; // �����ð�	
	InteractionCheckDistance = 500.0f; // Ž���Ÿ�

	// ...
}


// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}


// Called every frame
void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void UPlayerInteractionComponent::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	//�÷��̾��� ��Ʈ�ѷ��� ������
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// ��ũ�� ���� �������� ���콺 ��ǥ, ������ ����
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const float RayLength = 1500.0f;
	FHitResult HitResult;
	FVector Start = WorldLocation;
	FVector End = WorldLocation + (WorldDirection * RayLength);

	// ��ü�� �浹�� ���� �ʴ� �Լ� �����(�÷��̾� ��ü)
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// ������� ���� ���̸� �ð�ȭ�մϴ�.
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 10, 2.0f, 1);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		// ���� ĳ��Ʈ�� �浹�� ���
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			if (HitResult.GetActor() != InteractionData.CurrentInteractable)
			{
				FoundInteractable(HitResult.GetActor());
				return;
			}
			else
			{
				return;
			}
		}
	}

	// ������ ����ϴ� ��ü ���ؿ��� ����ĳ��Ʈ�� �Ǻ����
	//FVector TraceStart{ GetOwner()->GetActorLocation() };
	//FVector TraceEnd{ TraceStart + (GetOwner()->GetActorForwardVector() * InteractionCheckDistance) };
	//
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0, 2.0f, 1);
	//
	//FCollisionQueryParams QueryParams;
	//QueryParams.AddIgnoredActor(GetOwner());
	//
	//FHitResult TraceHit;
	//
	//if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	//{
	//	if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	//	{
	//		const float Distance = (TraceStart - TraceHit.ImpactPoint).Size();
	//
	//		if (TraceHit.GetActor() != InteractionData.CurrentInteractable && Distance <= InteractionCheckDistance)
	//		{
	//			FoundInteractable(TraceHit.GetActor());
	//			return;
	//		}
	//
	//		if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
	//		{
	//			return;
	//		}
	//	}
	//}
	NoInteractableFound();
}

void UPlayerInteractionComponent::FoundInteractable(AActor* NewInteractable)
{
	if (bIsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void UPlayerInteractionComponent::NoInteractableFound()
{
	if (bIsInteracting())
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandleInteraction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD->HideInteractionWidget();


		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void UPlayerInteractionComponent::BeginInteract()
{
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.7f))
			{
				Interact();
			}
			else
			{
				GetOwner()->GetWorldTimerManager().SetTimer(
					TimerHandleInteraction,
					this,
					&UPlayerInteractionComponent::Interact,
					TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void UPlayerInteractionComponent::EndInteract()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandleInteraction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void UPlayerInteractionComponent::Interact()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandleInteraction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		APlayerCharacter* CharacterTemp = Cast<APlayerCharacter>(GetOwner());
		TargetInteractable->Interact(CharacterTemp);
	}
}

void UPlayerInteractionComponent::ToggleMenu()
{
	HUD->ToggleMenu();
}

void UPlayerInteractionComponent::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}
