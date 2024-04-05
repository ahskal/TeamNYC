// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerJabDataAsset.h"

UPlayerJabDataAsset::UPlayerJabDataAsset()
{
	// 몽타주 섹션 접두사
	MontageSectionNamePrefix = TEXT("UnarmedAttack_");

	// 몽타주 섹션 접미사
	MontageSectionNameSuffix.Add(TEXT("Left"));
	MontageSectionNameSuffix.Add(TEXT("Right"));
	MontageSectionNameSuffix.Add(TEXT("Combo"));
	MontageSectionNameSuffix.Add(TEXT("Finish"));

	// 최대 콤보 수
	MaxComboCount = 4;

	// 애니메이션 Frame Rate
	FramePerSceond = 30.0f;

	// 콤보중 사전에 입력된 커맨드가 있는지 감지할 프레임 수
	EffectiveFrameCount.Add(20.0f); // 31
	EffectiveFrameCount.Add(20.0f); // 31
	EffectiveFrameCount.Add(30.0f); // 65
	EffectiveFrameCount.Add(-1.0f); // 마지막 타격은 추가타를 감지할 필요가 없음
}
