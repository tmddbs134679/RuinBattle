// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "RBPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API ARBPlayerState : public APlayerState
{
	GENERATED_BODY()

		friend class APlayerCharacter;
		friend class AKnightCharacter;
		friend class ARuinBattleGameModeBase;

public:
	ARBPlayerState();


public:
	void InitPlayer();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	float GetZoomMin() const
	{
		return mZoomMin;
	}

	float GetZoomMax() const
	{
		return mZoomMax;
	}

	const FPlayerInfo& GetInfo() const
	{
		return	mPlayerInfo;
	}

	void SetAttackDistance(float Dist)
	{
		mPlayerInfo.AttackDistance = Dist;
	}
protected:

	UPROPERTY(VisibleAnywhere)
		float mZoomMin;

	UPROPERTY(VisibleAnywhere)
		float mZoomMax;

	UPROPERTY(VisibleAnywhere)
		FPlayerInfo mPlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FName				mPlayerTableRowName;




};
