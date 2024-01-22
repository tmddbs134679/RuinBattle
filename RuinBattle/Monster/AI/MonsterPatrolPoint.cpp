// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPatrolPoint.h"

// Sets default values
AMonsterPatrolPoint::AMonsterPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	SetRootComponent(mRoot);

	//mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void AMonsterPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

