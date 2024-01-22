// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components\ProgressBar.h>
#include "MonsterHPBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UMonsterHPBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:
	void SetHP(float Ratio);

public:

	void SetInitHP(float Ratio)
	{
		mMonsterInitRatio = Ratio;
	}

private:
	float mMonsterInitRatio;


private:
	UProgressBar* mHPBar;

};
