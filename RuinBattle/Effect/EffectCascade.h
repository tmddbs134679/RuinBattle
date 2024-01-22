// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Effect.h"
#include "EffectCascade.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AEffectCascade : public AEffect
{
	GENERATED_BODY()
	

public:
	AEffectCascade();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetParticle(UParticleSystem* Particle);
	virtual void SetParticle(const FString& Path);

public:
	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* mParticle;
};
