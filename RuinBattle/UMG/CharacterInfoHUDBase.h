// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "CharacterInfoHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UCharacterInfoHUDBase : public UUserWidget
{
	GENERATED_BODY()


		
public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

private:
	UButton* mCancelBtn;

};
