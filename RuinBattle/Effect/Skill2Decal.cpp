// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill2Decal.h"

// Sets default values
ASkill2Decal::ASkill2Decal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("DECAL"));

	SetRootComponent(mRoot);

	mDecal->SetupAttachment(mRoot);

	mRoot->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	//mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void ASkill2Decal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill2Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkill2Decal::SetDecalMtrl(const FString& Path)
{
	UMaterialInterface* Mtrl = LoadObject<UMaterialInterface>(nullptr, *Path);

	if (IsValid(Mtrl))
		mDecal->SetDecalMaterial(Mtrl);
}

