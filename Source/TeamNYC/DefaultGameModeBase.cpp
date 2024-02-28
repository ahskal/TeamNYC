// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameModeBase.h"

ADefaultGameModeBase::ADefaultGameModeBase()
{
	// Set default pawn class
	FString Path = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C'");
	//static void GetClass(TSubclassOf<T>*OutClass, const FString & Path)
	ConstructorHelpers::FClassFinder<APawn> ClassFinder(*Path);
	if (ClassFinder.Succeeded()) DefaultPawnClass = ClassFinder.Class;
	else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *Path);
}
