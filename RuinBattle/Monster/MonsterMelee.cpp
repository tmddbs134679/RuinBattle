// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMelee.h"
#include "MonsterAIController.h"
#include "../Effect/EffectNiagara.h"

AMonsterMelee::AMonsterMelee()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeleeAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/White_Camp_Minion/Meshes/Minion_melee.Minion_melee'"));

	if (MeleeAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeleeAsset.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("AnimBlueprint'/Game/Monster/ABMelee.ABMelee_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);


	GetCapsuleComponent()->SetCapsuleHalfHeight(70.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("Melee");

}

void AMonsterMelee::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterMelee::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMonsterMelee::UnPossessed()
{
	Super::UnPossessed();
}

void AMonsterMelee::Attack()
{

	AAIController* MonsterController = Cast<AAIController>(GetController());

	ACharacter* Target = Cast<ACharacter>(MonsterController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (IsValid(Target))
	{
		Target->TakeDamage(
			(float)mMonsterInfo.AttackPoint,
			FDamageEvent(), GetController(), this);


		FVector Location = GetMesh()->GetBoneLocation(TEXT("Weapon_r"));
		
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectNiagara* Particle = GetWorld()->SpawnActor<AEffectNiagara>(
			Location,
			GetActorForwardVector().Rotation(),
			SpawnParam);


		Particle->SetParticle(TEXT("NiagaraSystem'/Game/Hack_And_Slash_FX/VFX_Niagara/Impacts/NS_Curse_Slash_Impact.NS_Curse_Slash_Impact'"));
		Particle->SetSound(TEXT("SoundWave'/Game/Sound/Sound/Fire1.Fire1'"));

	}

}
