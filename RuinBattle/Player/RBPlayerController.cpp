// Fill out your copyright notice in the Description page of Project Settings.


#include "RBPlayerController.h"
#include "../Skill/SkillProjectile.h"
#include "PlayerCharacter.h"
#include "../Effect/EffectCascade.h"
#include "KnightCharacter.h"

ARBPlayerController::ARBPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SkillMouseCursorEnable = false;

}

void ARBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	mSkillMouseCursor = GetWorld()->SpawnActor<ASkill2Decal>(FVector::ZeroVector, FRotator::ZeroRotator);
}

void ARBPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	mSkillMouseCursor->SetDecalMtrl(TEXT("Material'/Game/Material/MTGhost.MTGhost'"));

	FHitResult Result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, Result);

	if(SkillMouseCursorEnable)
	{
		bEnableMouseOverEvents = true;

		if (Hit)
		{
			mSkillMouseCursor->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
			mSkillMouseCursor->SetVisibility(true);
			mSkillMouseCursor->SetActorLocation(Result.ImpactPoint);
		}
		
	}

}

void ARBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ARBPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARBPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ARBPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ARBPlayerController::Skill2MousePick()
{

	SkillMouseCursorEnable = true;

}

void ARBPlayerController::Skill2Meteor()
{
	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	//Meteor ������ġ Decal�� �����մϴ�.
	ASkill2Decal* Decal =
		GetWorld()->SpawnActor<ASkill2Decal>(
			mSkillMouseCursor->GetActorLocation(),
			FRotator(0.f, mSkillMouseCursor->GetActorRotation().Yaw, 0.f),
			SpawnParam);

	Decal->SetDecalMtrl(TEXT("Material'/Game/Material/MTGhost.MTGhost'"));
	Decal->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	Decal->SetLifeSpan(1.f);

	SkillMouseCursorEnable = false;
	mSkillMouseCursor->SetVisibility(false);

	//Meteor�� �����մϴ�.
	ASkillProjectile* Meteor = GetWorld()->SpawnActor<ASkillProjectile>(
		mSkillMouseCursor->GetActorLocation() +  FVector(0.f, 0.f, 3000.f),
		FRotator(-90.f,0.f,0.f),
		SpawnParam);
	
	Meteor->SetActorScale3D(FVector(5.f, 5.f, 5.f));
	Meteor->SetStaticMesh(TEXT("StaticMesh'/Game/ParagonMinions/FX/Meshes/Shapes/SM_BlobbySphere.SM_BlobbySphere'"));
	Meteor->SetParticle(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
	Meteor->GetProjectile()->ProjectileGravityScale = 5.f;

	//Protile Actor�� �ʹ� Ŀ�� �浹�� �ٴ����θ� �Ǳ� ������ ���͸� �浹 ó���ǰ� ��ų �������� ����
	Meteor->SetCollisionProfile(TEXT("KnightSkill2"));
	
}
