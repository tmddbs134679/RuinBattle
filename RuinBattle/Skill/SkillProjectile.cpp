// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillProjectile.h"
#include "../Monster/Monster.h"
#include "../Player/RBPlayerController.h"
#include"../Player/PlayerCharacter.h"

ASkillProjectile::ASkillProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));


	mProjectile->InitialSpeed = 1000.f;
	mProjectile->ProjectileGravityScale = 0.f;

	mProjectile->SetUpdatedComponent(mRoot);

	mProjectile->OnProjectileStop.AddDynamic(this, &ASkillProjectile::CollisionProfile);
	mDistance = -1.f;

	mPrevLocation = GetActorLocation();
}

void ASkillProjectile::BeginPlay()
{
	Super::BeginPlay();


	mProjectile->OnProjectileStop.AddDynamic(this, &ASkillProjectile::CollisionProfile);

	mPrevLocation = GetActorLocation();
}

void ASkillProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mDistance > -1.f)
	{
		float Distance = FVector::Distance(mPrevLocation, GetActorLocation());

		mDistance -= Distance;

		if (Distance <= 0.f)
			Destroy();

		else
			mPrevLocation = GetActorLocation();
	}
}

void ASkillProjectile::CollisionProfile(const FHitResult& Hit)
{
	PrintViewport(1.f, FColor::Red, TEXT("Hit"));


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	//스킬 몬스터 가격 시 CollisionProfile에서 TakeDamage
	Hit.GetActor()->TakeDamage(20,
		FDamageEvent(),
		PlayerController,
		this);

	
	//Broadcast : 함수 여러 개 동시 호출 가능.
	mOnSkillEnd.Broadcast(this, Hit);
	
	this->Destroy();
}

