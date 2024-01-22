// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/Button.h>
#include "../GameInfo.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UStartHUDBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

public:
	
	UFUNCTION()
	void OnStartBtnClicked();

	UFUNCTION()
		void OnStartBtnHover();

	UFUNCTION()
		void OnStartBtnUnHover();


	UFUNCTION()
		void OnEndBtnClicked();

	UFUNCTION()
		void OnEndBtnHover();

	UFUNCTION()
		void OnEndBtnUnHover();


private:
	UButton* mStartBtn;
	UButton* mEndBtn;


public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivatedAccess = true))
		FName	mNextLevelName;

	TMap <FString, UWidgetAnimation*> mWidgetAim;

};
