// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoBase.h"
#include "../Player/RBPlayerState.h"


void UPlayerInfoBase::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("HPBar"))));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("MPBar"))));
	mLevelBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("LevelTextBlock"))));
}

void UPlayerInfoBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}




void UPlayerInfoBase::SetHP(float Ratio)
{
	mHPBar->SetPercent(Ratio);

}

void UPlayerInfoBase::SetMP(float Ratio)
{
	mMPBar->SetPercent(Ratio);
}

void UPlayerInfoBase::SetLevel(int Level)
{
	mLevelBlock->SetText(FText::FromString(FString::FromInt(Level)));
}

