#include "Components/PlayerInteractionComponent.h"
#include "Components/InventoryComponents/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/InteractionInterface/InteractionInterface.h"
#include "UserInterface/PlayerHUD.h"
#include "Item/Pickup.h"
#include "Item/LootItem.h"

#include "GameFramework/Character.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = true;

	InteractionCheckFrequency = 0.1f; // 지연시간	
	InteractionCheckDistance = 500.0f; // 탐색거리
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

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

	//플레이어의 컨트롤러를 가져옴
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	// 스크린 센터 기준으로 마우스 좌표, 방향을 구함
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const float RayLength = 1500.0f;
	FHitResult HitResult;
	FVector Start = WorldLocation;
	FVector End = WorldLocation + (WorldDirection * RayLength);

	// 객체과 충돌을 하지 않는 함수 라고함(플레이어 객체)
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// 디버깅을 위해 레이를 시각화합니다.
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 10, 2.0f, 1);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		// 레이 캐스트가 충돌한 경우
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

void UPlayerInteractionComponent::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	APlayerCharacter* CharacterTemp = Cast<APlayerCharacter>(GetOwner());
	UItemBase* FoundItem = CharacterTemp->GetInventory()->FindMatchingItem(ItemToDrop);
	if (FoundItem)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation{ GetOwner()->GetActorLocation() + FVector(0.f,45.f,0.f) + (GetOwner()->GetActorForwardVector() * 235.f) };
		//const FVector SpawnLocation{ GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 50.f) };
		const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);

		const int32 RemovedQuantity = CharacterTemp->GetInventory()->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		ALootItem* LootItem = GetWorld()->SpawnActor<ALootItem>(ALootItem::StaticClass(), SpawnTransform, SpawnParams);
		LootItem->InitializeDrop(ItemToDrop, RemovedQuantity);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop is null!"));
	}
}
