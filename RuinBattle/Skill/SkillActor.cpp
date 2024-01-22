// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor.h"

// Sets default values
ASkillActor::ASkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USphereComponent>(TEXT("ROOT"));

	SetRootComponent(mRoot);

	mSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mSound = nullptr;

	mSkeletalMesh->SetupAttachment(mRoot);
	mStaticMesh->SetupAttachment(mRoot);
	mParticle->SetupAttachment(mRoot);

	//mRoot->bVisualizeComponent = true;

	mActorLifeTime = 3.f;
	
}

// Called when the game starts or when spawned
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillActor::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);

	mOnSkillEnd.Clear();
}

// Called every frame
void ASkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mActorLifeTime -= DeltaTime;

	if (mActorLifeTime <= 0)
	{
		Destroy();
	}

}

void ASkillActor::SetSkeletalMesh(const FString& Path)
{

	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(
		nullptr, *Path);

	if (IsValid(mSkeletalMesh))
		mSkeletalMesh->SetSkeletalMesh(SkeletalMesh);
}

void ASkillActor::SetStaticMesh(const FString& Path)
{
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(
		nullptr, *Path);

	if (IsValid(mStaticMesh))
		mStaticMesh->SetStaticMesh(StaticMesh);
}

void ASkillActor::SetParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(
		nullptr, *Path);

	if (IsValid(mParticle))
		mParticle->SetTemplate(Particle);

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


}

void ASkillActor::SetSound(const FString& Path)
{
	mSound = LoadObject<USoundBase>(nullptr, *Path);
}

void ASkillActor::SetBoxExtent(const FVector& Extent)
{
}

void ASkillActor::SetCollisionProfile(const FName& Profile)
{
	mRoot->SetCollisionProfileName(Profile);
}


void ASkillActor::SetNiagara(UNiagaraSystem* Niagara)
{
	if (IsValid(Niagara))
		mNiagara->SetAsset(Niagara);

}

void ASkillActor::SetNiagara(const FString& Path)
{
	UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, *Path);

	if (IsValid(Niagara))
		mNiagara->SetAsset(Niagara);
}

