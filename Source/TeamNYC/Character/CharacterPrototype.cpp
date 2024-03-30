// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPrototype.h"

// Sets default values
ACharacterPrototype::ACharacterPrototype()
{
	UE_LOG(LogTemp, Display, TEXT("==================== CharacterPrototype ===================="));
}

// Called when the game starts or when spawned
void ACharacterPrototype::BeginPlay()
{
	Super::BeginPlay();
}
