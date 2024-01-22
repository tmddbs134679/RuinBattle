// Fill out your copyright notice in the Description page of Project Settings.


#include "RBPostProcessVolume.h"

ARBPostProcessVolume::ARBPostProcessVolume()
{

	APostProcessVolume::bUnbound;

	mTint = Settings.BloomDirtMaskTint;
	mIntensity = Settings.BloomDirtMaskIntensity;
}
