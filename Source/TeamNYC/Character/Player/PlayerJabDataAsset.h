// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerJabDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TEAMNYC_API UPlayerJabDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPlayerJabDataAsset();

	// 몽타주 섹션 접두사
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FString MontageSectionNamePrefix;

	// 몽타주 섹션 접미사
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	TArray<FString> MontageSectionNameSuffix;

	// 최대 콤보 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	uint8 MaxComboCount;

	// 애니메이션 Frame Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	float FramePerSceond;

	// 콤보중 사전에 입력된 커맨드가 있는지 감지할 프레임 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	TArray<float> EffectiveFrameCount;
};
