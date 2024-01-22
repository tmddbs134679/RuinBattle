// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawn.h"
#include "Monster.h"
#include "AI/MonsterPatrolPoint.h"

// Sets default values
AMonsterSpawn::AMonsterSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	SetRootComponent(mRoot);

	//mRoot->bVisualizeComponent = true;

	mSpawnCount = 1;
	mSpawnTime = 5.f;

	mTime = 0;

}

// Called when the game starts or when spawned
void AMonsterSpawn::BeginPlay()
{
	Super::BeginPlay();

	mPatrolPointLocArr.Add(GetActorLocation());

	int32 PatrolPointCount = mPatrolPointArr.Num();

	for (int32 i = 0; i < PatrolPointCount; i++)
	{
		mPatrolPointLocArr.Add(mPatrolPointArr[i]->GetActorLocation());
	}
	
	if (IsValid(mSpawnClass))
	{
		mSpawnCount = mSpawnCount < 1 ? 1 : mSpawnCount;

		//�����浹 �ذ�
		FActorSpawnParameters SpawnParam;

		//�����浹 �� �浹���� �ʴ� ��ó�� ����
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMonster* SpawnMonster =
			GetWorld()->SpawnActor<AMonster>(
				mSpawnClass,
				GetActorLocation(),
				GetActorRotation(),
				SpawnParam);
		
		SpawnMonster->SetSpawnPoint(this);
		SpawnMonster->SetPatrolPointLocation(mPatrolPointLocArr);
		SpawnMonster->SetPatrolDir(mPatrolDir);

		mMonsterArr.Add(SpawnMonster);
	}
}

// Called every frame
void AMonsterSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (IsValid(mSpawnClass))
	{
		if (mMonsterArr.Num() < mSpawnCount)
		{
			mTime += DeltaTime;
			
			if (mTime >= mSpawnTime)
			{
				mTime -= mSpawnTime;

				//�����浹 �ذ�
				FActorSpawnParameters SpawnParam;

				//�����浹 �� �浹���� �ʴ� ��ó�� ����
				SpawnParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AMonster* SpawnMonster =
					GetWorld()->SpawnActor<AMonster>(
						mSpawnClass,
						GetActorLocation(),
						GetActorRotation(),
						SpawnParam);


				SpawnMonster->SetSpawnPoint(this);
				SpawnMonster->SetPatrolPointLocation(mPatrolPointLocArr);
				SpawnMonster->SetPatrolDir(mPatrolDir);


				if (mMonsterArr.Num() == mSpawnCount)
					mTime = 0.f;
			}
		}
	}
}

