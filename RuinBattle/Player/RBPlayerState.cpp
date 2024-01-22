// Fill out your copyright notice in the Description page of Project Settings.


#include "RBPlayerState.h"
#include "../RuinBattleGameModeBase.h"
#include "../RBSaveGame.h"
#include "../RBGameInstance.h"

//
//레벨 전환 데이터 유지 방법 1. 지워지지 않는 gameinstance에 저장해서 복사
//						     2. file에 저장해서 db처럼 사용

ARBPlayerState::ARBPlayerState()
{
	mZoomMin = 800.f;
	mZoomMax = 1000.f;
	mPlayerInfo.AttackDistance = 150.f;
}

void ARBPlayerState::InitPlayer()
{
	mZoomMin = 800.f;
	mZoomMax = 1000.f;
	mPlayerInfo.AttackDistance = 150.f;
}

void ARBPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ARuinBattleGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ARuinBattleGameModeBase>();

	GameMode->GetSaveGame()->mPlayerInfo = mPlayerInfo;
	GameMode->GetSaveGame()->mZoomMax = mZoomMax;
	GameMode->GetSaveGame()->mZoomMin = mZoomMin;
}
