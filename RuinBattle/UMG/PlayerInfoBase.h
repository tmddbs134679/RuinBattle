// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include <Components\ProgressBar.h>
#include <Components/TextBlock.h>
#include "PlayerInfoBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UPlayerInfoBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:
	void SetHP(float Ratio);
	void SetMP(float Ratio);
	void SetLevel(int Level);



private:
	UProgressBar* mHPBar;
	UProgressBar* mMPBar;
	UTextBlock* mLevelBlock;

};
