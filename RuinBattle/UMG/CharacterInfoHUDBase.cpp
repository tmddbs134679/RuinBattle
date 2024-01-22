// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInfoHUDBase.h"
#include "../Player/RBPlayerController.h"


void UCharacterInfoHUDBase::NativeConstruct()
{

	Super::NativeConstruct();

	mCancelBtn = Cast<UButton>(GetWidgetFromName(TEXT("CancleBtn")));

	

}

void UCharacterInfoHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}

