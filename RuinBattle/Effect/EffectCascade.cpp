// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectCascade.h"

AEffectCascade::AEffectCascade()
{
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));

	mParticle->SetupAttachment(mAudio);
}

void AEffectCascade::BeginPlay()
{
	Super::BeginPlay();

	//OnSystemFinished : Particle system finish -> call
	mParticle->OnSystemFinished.AddDynamic(this, &AEffectCascade::ParticleFinish);
}


void AEffectCascade::SetParticle(UParticleSystem* Particle)
{
	if (IsValid(Particle))
		mParticle->SetTemplate(Particle);
}

void AEffectCascade::SetParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(
		nullptr, *Path);

	if (IsValid(Particle))
		mParticle->SetTemplate(Particle);
}

void AEffectCascade::ParticleFinish(UParticleSystemComponent* Particle)
{
	Destroy();
}
