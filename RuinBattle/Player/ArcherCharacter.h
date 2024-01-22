// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "PlayerCharacter.h"
#include "ArcherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AArcherCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AArcherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttackCheck();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();
	virtual void UseSkill(int32 SkillNum);
	virtual void MoveSide(float Scale);
};
