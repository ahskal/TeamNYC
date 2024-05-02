// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameModeBase.h"
#include "UserInterface/PlayerHUD.h"

ADefaultGameModeBase::ADefaultGameModeBase()
{
	UE_LOG(LogTemp, Display, TEXT("==================== DefaultGameModeBase ===================="));

	// Set default pawn class
	FString PawnPath = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C'");
	ConstructorHelpers::FClassFinder<APawn> PawnClassFinder(*PawnPath);
	if (PawnClassFinder.Succeeded()) DefaultPawnClass = PawnClassFinder.Class;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *PawnPath);

	// Set default player controller class
	// Mouse
	FString MouseControllerPath = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Characters/Input/BP_MousePlayerController.BP_MousePlayerController_C'");
	ConstructorHelpers::FClassFinder<APlayerController> MouseControllerClassFinder(*MouseControllerPath);
	if (MouseControllerClassFinder.Succeeded())
	{
		PlayerControllerClass = MouseControllerClassFinder.Class;
	}
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *MouseControllerPath);

	// Keyboard
	//FString KeyboardControllerPath = TEXT("/Script/CoreUObject.Class'/Script/TeamNYC.KeyboardPlayerController'");
	//ConstructorHelpers::FClassFinder<APlayerController> KeyboardControllerClassFinder(*KeyboardControllerPath);
	//if (KeyboardControllerClassFinder.Succeeded()) UE_LOG(LogTemp, Display, TEXT("Succeeded to Get Class: %s"), *KeyboardControllerPath)
	//else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *KeyboardControllerPath); UE_LOG(LogTemp, Display, TEXT(""));


	// 블루프린트 객체를 불러오는 방법중 하나
	//FString HUDPath = TEXT("/Script/Engine.Blueprint'/Game/UserInterface/BP_PlayerHUD.BP_PlayerHUD_C'");
	//FStringClassReference HUDClassRef(HUDPath);
	//if (UClass* HUDclass = HUDClassRef.TryLoadClass<AHUD>())
	//{
	//	this->HUDClass = HUDclass;
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Failed to load HUD class: %s"), *HUDClassRef.GetAssetName());
	//}
	
	// C++로 작성된 객체를 불러올때
	//HUDClass = APlayerHUD::StaticClass();

	// Set default HUD class
	// AGameModeBase내부에 HUDClass 멤버에 BP객체 값 할당
	// Create Pawn 방식과 동일함
	FString HUDPath = TEXT("/Script/Engine.Blueprint'/Game/UserInterface/BP_PlayerHUD.BP_PlayerHUD_C'");
	ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(*HUDPath);
	if (HUDClassFinder.Succeeded()) HUDClass = HUDClassFinder.Class;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *HUDPath);
}
