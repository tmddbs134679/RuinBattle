// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Monster.h"
#include "MonsterBoss.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AMonsterBoss : public AMonster
{
	GENERATED_BODY()
	
public:
	AMonsterBoss();

public:
	virtual void OnConstruction(const FTransform& Transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();
	virtual void Attack();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();

protected:
	AActor* mMuzzleParticle;

protected:

};
