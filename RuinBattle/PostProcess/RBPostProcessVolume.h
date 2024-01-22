// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/PostProcessVolume.h"
#include "RBPostProcessVolume.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API ARBPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
		ARBPostProcessVolume();


public:
	void SetDirTint(FLinearColor Tint)
	{
		mTint = Tint;
	}
	void SetDirIntensity(float Intensity)
	{
		mIntensity = Intensity;
	}

private:
	FLinearColor mTint;

	float mIntensity;

};
