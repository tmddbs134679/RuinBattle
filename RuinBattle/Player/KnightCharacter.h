// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "PlayerCharacter.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AKnightCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AKnightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void NormalAttackCheck();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill2Released();


	virtual void Skill3();
	virtual void UseSkill(int32 SkillNum);
	virtual void SavePlayer();

protected:
	
	UNiagaraSystem* mAttackSystem;

	AActor* mAttackParticle;

	bool mSkill2Enable;
	





public:
	UFUNCTION()
	void Skill1End(class ASkillActor* SkillActor, const FHitResult& Hit);
	void Skill2End(class ASkillActor* SkillActor, const FHitResult& Hit);
};
