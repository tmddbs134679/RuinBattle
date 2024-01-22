// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include <Components/WidgetComponent.h>

#include "Monster.generated.h"


UCLASS()
class RUINBATTLE_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual void OnConstruction(const FTransform& Transform);
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();
	virtual void Attack();

public:

	void AddPatrolWaitTime(float Time)
	{
		mPatrolWaitTime += Time;
	}

	void ClearPatrolWaitTime()
	{
		mPatrolWaitTime = 0.f;
	}

	bool GetPatrolEnable() const
	{
		return mPatrolPointLocArr.Num() >= 2;
	}

	void NextPatrolPoint()
	{
		mPatrolIndex += mPatrolIndexAdd;

		if (mPatrolIndex == mPatrolPointLocArr.Num())
		{
			switch (mPatrolDir)
			{
			case EPatrolEndDir::Progress:
				mPatrolIndex = 0;

				break;
			case EPatrolEndDir::Repeat:
				break;
			}
		}
		else if (mPatrolIndex < 0)
		{
			mPatrolIndexAdd = 1;
			mPatrolIndex = 1;
		}
	}

public:

	const FMonsterInfo& GetMonsterInfo() const
	{
		return mMonsterInfo;
	}

	class UMonsterAniminstance* GetMonsterAnimInst() const
	{
		return mAnimInst;
	}

	bool GetMonsterAttackEnd()
	{
		return mAttackEnd;
	}

	float GetPartrolWaitTime() const
	{
		return mPatrolWaitTime;
	}

	const FVector& GetPatrolLocation() const
	{
		return mPatrolPointLocArr[mPatrolIndex];
	}

	int32 GetUseSkillIndex() const
	{
		return mUseSkillIndex;
	}

	const FMonsterSkillInfo* GetSkillData()
	{
		if (mUseSkillIndex == -1)
			return nullptr;

		return &mSkillDataArr[mUseSkillIndex];
	}

	UWidgetComponent* GetWidgetComponent()
	{
		return mWidgetComponent;
	}


public:

	void SetMonsterAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}

	void SetSpawnPoint(class AMonsterSpawn* SpawnPoint)
	{
		mSpawnPoint = SpawnPoint;
	}
	
	void SetPatrolPointLocation(const TArray<FVector>& Array)
	{
		mPatrolPointLocArr = Array;
	}

	void SetPatrolDir(EPatrolEndDir Dir)
	{
		mPatrolDir = Dir;
	}
protected:

	class UMonsterAniminstance* mAnimInst;

	class AMonsterSpawn* mSpawnPoint;

	bool	 mAttackEnd;
	float	mPatrolWaitTime;
	int32	mPatrolIndex;
	int32	mPatrolIndexAdd;

	int32 mUseSkillIndex;


	AActor* mHitActor;

	TArray<FVector> mPatrolPointLocArr;
	EPatrolEndDir	mPatrolDir;


public:

	UFUNCTION(BlueprintCallable)
	void LevelStartAI();

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FMonsterInfo	mMonsterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FName	mMonsterTableRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<FName>	mSkillNameArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mSkillEnable;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))

	TArray<FMonsterSkillInfo>	mSkillDataArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))

	UWidgetComponent* mWidgetComponent;



};
