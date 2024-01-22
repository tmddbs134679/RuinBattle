// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUDBase.h"
#include "../Player/RBPlayerState.h"

void UCharacterHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerInfo = Cast<UPlayerInfoBase>(GetWidgetFromName(FName(TEXT("PlayerInfo"))));
	mInventory = Cast<UInventoryBase>(GetWidgetFromName(FName(TEXT("Inventory"))));
	mExplanation = Cast<UExplanationBase>(GetWidgetFromName(FName(TEXT("Explanation"))));
	mCharacterInfoHUDBase = Cast<UCharacterInfoHUDBase>(GetWidgetFromName(FName("CharacterInfo")));
}

void UCharacterHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

void UCharacterHUDBase::SetHP(float Ratio)
{
	mPlayerInfo->SetHP(Ratio);
}

void UCharacterHUDBase::SetMP(float Ratio)
{
	mPlayerInfo->SetMP(Ratio);

}

void UCharacterHUDBase::SetLevel(int Level)
{
	mPlayerInfo->SetLevel(Level);
}
