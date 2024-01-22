// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBoss.h"
#include "MonsterAIController.h"
#include "../Effect/EffectCascade.h"


AMonsterBoss::AMonsterBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BossAsset(TEXT("SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Skins/Tier_1/Muriel_Black/Meshes/MurielBlack.MurielBlack'"));

	if (BossAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BossAsset.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("AnimBlueprint'/Game/Monster/ABBoss.ABBoss_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	//AEffectCascade* Particle = Cast<AEffectCascade>(mHitActor);
	//Particle->SetParticle(TEXT(""));

	mMonsterTableRowName = TEXT("Boss");

	mSkillNameArr.Add(TEXT("BossSkill1"));
	mSkillNameArr.Add(TEXT("BossSkill2"));
	mSkillNameArr.Add(TEXT("BossSkill3"));


}

void AMonsterBoss::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterBoss::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterBoss::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMonsterBoss::UnPossessed()
{
	Super::UnPossessed();
}

void AMonsterBoss::Attack()
{
	PrintViewport(1.f, FColor::Red, TEXT("BossAttack"));

	FVector MuzzleLocation = GetMesh()->GetSocketLocation(TEXT("Aim_Target"));

	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEffectCascade* MuzzleParticle =
		GetWorld()->SpawnActor<AEffectCascade>(
			MuzzleLocation,
			GetActorForwardVector().Rotation(),
			SpawnParam);

	//MuzzleParticle->SetParticle(TEXT("NiagaraSystem'/Game/sA_Megapack_v1/sA_Projectilevfx/Vfx/Fx/Niagara_Systems/NS_Muzzle_6.NS_Muzzle_6'"));

	FVector AttackEnd = MuzzleLocation + GetActorForwardVector() * mMonsterInfo.AttackDistance - 50.f;

	FCollisionQueryParams Param(NAME_None, false, this);

	FHitResult Result;

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		Result,
		MuzzleLocation,
		AttackEnd,
		ECollisionChannel::ECC_GameTraceChannel8,
		Param);

#if ENABLE_DRAW_DEBUG
	FColor	Color = Hit ? FColor::Red : FColor::Green;

	DrawDebugLine(GetWorld(), MuzzleLocation, AttackEnd, Color, false, 1.f, 2.f);

#endif


	if (Hit)
	{
		FActorSpawnParameters	HitSpawnParam;
		HitSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectCascade* Particle =
			GetWorld()->SpawnActor<AEffectCascade>(
				Result.ImpactPoint,
				Result.ImpactNormal.Rotation(),
				HitSpawnParam);

		Particle->SetParticle(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_hit2.P_ky_hit2'"));

		Result.GetActor()->TakeDamage(
			(float)mMonsterInfo.AttackPoint,
			FDamageEvent(), 
			GetController(), 
			this);
	
	}
}

void AMonsterBoss::Skill1()
{
	AAIController* MonsterController = Cast<AAIController>(GetController());

	ACharacter* Target = Cast<ACharacter>(MonsterController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if(IsValid(Target))
	{
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Dir = GetActorLocation() - Target->GetActorLocation();

		//정규화로 안전하게 수행
		Dir.Normalize();

		FVector ParticleLocation = Target->GetActorLocation() + Dir;

		AEffectCascade* Particle =
			GetWorld()->SpawnActor<AEffectCascade>(
				ParticleLocation,
				Dir.Rotation(),
				SpawnParam);

		UNiagaraSystem* Play = nullptr;
		UNiagaraSystem* Cast = nullptr;
		UNiagaraSystem* Trail = nullptr;


		int EffectCount = mSkillDataArr[mUseSkillIndex].SkillEffectArr.Num();

		for (int32 i = 0; i < EffectCount; ++i)
		{
			switch (mSkillDataArr[mUseSkillIndex].SkillEffectArr[i].Type)
			{
			case ESkillEffectType::Cast:
				break;
			case ESkillEffectType::Play:
				Play = mSkillDataArr[mUseSkillIndex].SkillEffectArr[i].Effect;
				break;
			case ESkillEffectType::Trail:
				break;
			}

		}
		
		float Damage = 0.f;

		int32 Count = mSkillDataArr[mUseSkillIndex].SkillOptionArr.Num();

		for (int32 i = 0; i < Count; ++i)
		{
			if (mSkillDataArr[mUseSkillIndex].SkillOptionArr[i].Type == ESkillOptionType::Damage)
				Damage += mSkillDataArr[mUseSkillIndex].SkillOptionArr[i].Option;
		}

		Damage = Damage <= 0 ? 1.f : Damage;

		Target->TakeDamage(
			mMonsterInfo.AttackPoint,
			FDamageEvent(),
			GetController(),
			this );

	}
}

void AMonsterBoss::Skill2()
{
}

void AMonsterBoss::Skill3()
{
}
