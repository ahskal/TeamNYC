// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ProgressBar/StatBar.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UStatBar::NativeConstruct()
{
	Super::NativeConstruct();

	StatBar->SetFillColorAndOpacity(BarColor);
	DynamicMaterialInstance = StatRemoveBar->GetDynamicMaterial();
	DynamicMaterialInstance->SetVectorParameterValue("Color", RemoveBarColor);
}
