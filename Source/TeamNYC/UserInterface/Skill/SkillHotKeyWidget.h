// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillHotKeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API USkillHotKeyWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	USkillHotKeyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	//====================================================================================
	// MEMBER VARIABLES
	//====================================================================================
public:

};
