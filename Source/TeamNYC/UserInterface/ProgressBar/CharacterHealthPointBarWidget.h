// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/ExtendedUserWidget.h"
#include "CharacterHealthPointBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API UCharacterHealthPointBarWidget : public UExtendedUserWidget
{
	GENERATED_BODY()
	
public:
	UCharacterHealthPointBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;


public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrnetHp);
	void SetHpBarColor(FLinearColor NewColor);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
