// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Effect.h"
#include "EffectNiagara.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AEffectNiagara : public AEffect
{
	GENERATED_BODY()

public:
	AEffectNiagara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetParticle(UNiagaraSystem* Particle);
	virtual void SetParticle(const FString& Path);

public:
	UFUNCTION()
		void ParticleFinish(UNiagaraComponent* Particle);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UNiagaraComponent* mParticle;

	UNiagaraSystem* mParticleSys;

};
