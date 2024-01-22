// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectNiagara.h"

AEffectNiagara::AEffectNiagara()
{
	mParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));

	mParticle->SetupAttachment(mAudio);

	
}

void AEffectNiagara::BeginPlay()
{
	Super::BeginPlay();
	
	//OnSystemFinished : Particle system finish -> call
	mParticle->OnSystemFinished.AddDynamic(this, &AEffectNiagara::ParticleFinish);
}

void AEffectNiagara::SetParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mParticle->SetAsset(Particle);
}

void AEffectNiagara::SetParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);

	if (IsValid(Particle))
		mParticle->SetAsset(Particle);
}

void AEffectNiagara::ParticleFinish(UNiagaraComponent* Particle)
{
	Destroy();
}
