// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));

	SetRootComponent(mAudio);
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffect::SetSound(const FString& Path, bool Play)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);

		if (Play)
			mAudio->Play();
	}
}

void AEffect::SetSound(USoundBase* Sound, bool Play)
{
	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);

		if (Play)
			mAudio->Play();
	}
}

void AEffect::SetParticle(UParticleSystem* Particle)
{
}

void AEffect::SetParticle(UNiagaraSystem* Particle)
{
}

void AEffect::SetParticle(const FString& Path)
{
}

