// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameModeBase.h"

ADefaultGameModeBase::ADefaultGameModeBase()
{
	// Set default pawn class
	FString Path = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C'");
	//static void GetClass(TSubclassOf<T>*OutClass, const FString & Path)
	ConstructorHelpers::FClassFinder<APawn> PawnClassFinder(*Path);
	if (PawnClassFinder.Succeeded()) DefaultPawnClass = PawnClassFinder.Class;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *Path);

	// Set default player controller class
	Path = TEXT("/Script/CoreUObject.Class'/Script/TeamNYC.KeyboardPlayerController'");
	ConstructorHelpers::FClassFinder<APlayerController> ControllerClassFinder(*Path);
	if (ControllerClassFinder.Succeeded()) PlayerControllerClass = ControllerClassFinder.Class;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *Path);


}
