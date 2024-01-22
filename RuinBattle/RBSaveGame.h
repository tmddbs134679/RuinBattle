// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/SaveGame.h"
#include "RBSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API URBSaveGame : public USaveGame
{
	GENERATED_BODY()

		friend class APlayerCharacter;
		friend class ARBPlayerState;
		friend class ARuinBattleGameModeBase;

private:
	UPROPERTY()
	FPlayerInfo	mPlayerInfo;

	UPROPERTY()
	float	mZoomMin;

	UPROPERTY()
	float	mZoomMax;

	UPROPERTY()
	FVector	mLocation;

	UPROPERTY()
	FRotator	mRotation;

	UPROPERTY()
	FVector	mScale;

	
};
