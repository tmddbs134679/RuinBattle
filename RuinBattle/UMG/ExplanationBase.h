// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include <Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "CharacterInfoHUDBase.h"
#include "ExplanationBase.generated.h"


/**
 * 
 */
UCLASS()
class RUINBATTLE_API UExplanationBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


	void ShowExplanation();



private:
	UButton* mExplanBtn;

	UButton* mInfoBtn;

	UButton* mCancelBtn;


public:
	UFUNCTION()
	void OnInfoBtn();

	UFUNCTION()
	void OnExplanBtn();

	UFUNCTION()
	void OnCancelBtn();

};
