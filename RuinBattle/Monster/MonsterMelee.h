// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Monster.h"
#include "MonsterMelee.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AMonsterMelee : public AMonster
{
	GENERATED_BODY()

public:
	AMonsterMelee();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();
	virtual void Attack();
	
};
