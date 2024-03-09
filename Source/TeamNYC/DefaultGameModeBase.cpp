// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameModeBase.h"

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
		UE_LOG(LogTemp, Display, TEXT("Succeeded to Get Class: %s"), *MouseControllerPath);
		PlayerControllerClass = MouseControllerClassFinder.Class;
	}
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *MouseControllerPath);

	// Keyboard
	FString KeyboardControllerPath = TEXT("/Script/CoreUObject.Class'/Script/TeamNYC.KeyboardPlayerController'");
	ConstructorHelpers::FClassFinder<APlayerController> KeyboardControllerClassFinder(*KeyboardControllerPath);
	if (KeyboardControllerClassFinder.Succeeded()) UE_LOG(LogTemp, Display, TEXT("Succeeded to Get Class: %s"), *KeyboardControllerPath)
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *KeyboardControllerPath); UE_LOG(LogTemp, Display, TEXT(""));


}
