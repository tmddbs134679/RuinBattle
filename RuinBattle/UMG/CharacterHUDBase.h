// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Blueprint\UserWidget.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoBase.h"
#include "InventoryBase.h"
#include "ExplanationBase.h"
#include "CharacterInfoHUDBase.h"
#include "CharacterHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UCharacterHUDBase : public UUserWidget
{
	GENERATED_BODY()

		friend class UExplanationBase;

public:
	virtual	void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:
	void SetHP(float Ratio);
	void SetMP(float Ratio);
	void SetLevel(int Level);
public:

	UInventoryBase* GetInventoryWidget()
	{
		return mInventory;
	}

	UExplanationBase* GetExplanationWidget()
	{
		return mExplanation;
	}

	UCharacterInfoHUDBase* GetCharacterInfoWidget()
	{
		return mCharacterInfoHUDBase;
	}

	void ShowCharacterInfoWidget()
	{
		mCharacterInfoHUDBase->SetVisibility(ESlateVisibility::Visible);
	}

private:
	UPlayerInfoBase*	 mPlayerInfo;

	UInventoryBase*		 mInventory;

	UExplanationBase*	 mExplanation;

	UCharacterInfoHUDBase* mCharacterInfoHUDBase;

};
