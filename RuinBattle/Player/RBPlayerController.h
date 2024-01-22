// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../Effect/Skill2Decal.h"
#include "GameFramework/PlayerController.h"
#include "RBPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class RUINBATTLE_API ARBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARBPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();
	virtual void PostInitializeComponents() override;

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	void Skill2MousePick();
	void Skill2Meteor();

protected:
	class ASkill2Decal* mSkillMouseCursor;
	TWeakObjectPtr<AActor> mPickActor;

	bool SkillMouseCursorEnable;

};
