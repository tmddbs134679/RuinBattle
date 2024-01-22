// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SkillActor.h"
#include "SkillProjectile.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API ASkillProjectile : public ASkillActor
{
	GENERATED_BODY()
	
public:
	ASkillProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UProjectileMovementComponent* GetProjectile() const
	{
		return mProjectile;
	}

	void SetDistance(float Distance)
	{
		mDistance = Distance;
	}

public:
	float		 mDistance;
	FVector		 mPrevLocation;


public:
	UFUNCTION()
		void CollisionProfile(const FHitResult& Hit);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* mProjectile;
	
};
