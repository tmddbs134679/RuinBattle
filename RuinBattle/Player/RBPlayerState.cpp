// Fill out your copyright notice in the Description page of Project Settings.


#include "RBPlayerState.h"
#include "../RuinBattleGameModeBase.h"
#include "../RBSaveGame.h"
#include "../RBGameInstance.h"

//
//���� ��ȯ ������ ���� ��� 1. �������� �ʴ� gameinstance�� �����ؼ� ����
//						     2. file�� �����ؼ� dbó�� ���

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
