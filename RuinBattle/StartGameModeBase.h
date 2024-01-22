// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Blueprint\UserWidget.h>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStartGameModeBase();


public:
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

private:
	TSubclassOf<UUserWidget> mStartHUDClass;
	UUserWidget* mStartHUD;



};
