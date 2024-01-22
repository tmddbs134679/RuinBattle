// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Skill2Decal.generated.h"

UCLASS()
class RUINBATTLE_API ASkill2Decal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkill2Decal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void SetDecalMtrl(const FString& Path);

public:

	void SetDecalRotation(const FRotator& Rot)
	{
		mDecal->SetRelativeRotation(Rot);
	}

	void SetVisibility(bool Visible)
	{
		mDecal->SetVisibility(Visible);
	}


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UDecalComponent* mDecal;


};
