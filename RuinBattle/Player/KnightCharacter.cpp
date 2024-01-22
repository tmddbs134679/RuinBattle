
// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"
#include "RBPlayerState.h"
#include "RBPlayerController.h"
#include "PlayerAniminstance.h"
#include "../Effect/EffectCascade.h"
#include "../Effect/EffectNiagara.h"
#include "../Skill/SkillProjectile.h"
#include "../Effect/Skill2Decal.h"
#include "../Monster/MonsterAIController.h"
#include "../RuinBattleGameModeBase.h"



AKnightCharacter::AKnightCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KnightAsset(TEXT("SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Skins/Tier1/Count_RedRevo/Meshes/SM_Countess_RedRevo.SM_Countess_RedRevo'"));

	if (KnightAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(KnightAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass (TEXT("AnimBlueprint'/Game/Player/Animation/ABKnightCharacter.ABKnightCharacter_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	
	mPlayerTableRowName = TEXT("KnightCharacter");


}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	FSkillInfo SkillInfo;
	SkillInfo.Damage = 100;
	SkillInfo.SkillNum = 0;
	SkillInfo.SlotNum = 0;


	ASkillProjectile* SkillProjectile = NewObject<ASkillProjectile>(this, ASkillProjectile::StaticClass());

	SkillInfo.SkillActor = Cast<ASkillActor>(SkillProjectile);
	
	SkillProjectile->SetStaticMesh(TEXT("StaticMesh'/Game/ParagonCountess/FX/Meshes/Shapes/SM_projectile_sphere.SM_projectile_sphere'"));
	SkillProjectile->SetParticle(TEXT("ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Dragon/FX/P_Dragon_Fireball_Projectile.P_Dragon_Fireball_Projectile'"));
	SkillProjectile->SetSound(TEXT("SoundWave'/Game/Sound/Sound/Skill1Sound.Skill1Sound'"));
	SkillProjectile->SetCollisionProfile(TEXT("PlayerAttack"));


	SkillProjectile->mOnSkillEnd.AddDynamic(this, &AKnightCharacter::Skill1End);
	

	UProjectileMovementComponent* Projectlie = SkillProjectile->GetProjectile();

	Projectlie->InitialSpeed = 2000.f;
	Projectlie->ProjectileGravityScale = 0.f;

	mSkillInfoArr.Add(SkillInfo);
	
	mSkill2Enable = true;
}

void AKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AKnightCharacter::NormalAttackCheck()
{
	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 30.f;

	FVector EndLocation = StartLocation + GetActorForwardVector() * State->GetInfo().AttackDistance;

	//탐색지정 생성 
	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FHitResult> CollisionResult;
	bool CollisionEnable = GetWorld()->SweepMultiByChannel(
		CollisionResult, StartLocation,
		EndLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(50.f),
		param);

#if ENABLE_DRAW_DEBUG

	//CollisionEnable가 true이면 red, false면 green 저장
	FColor DrawColor = CollisionEnable ? FColor::Red : FColor::Green;


	//FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat()) : 앞쪽을 바라보는 회전행렬을 만들어서 .ToQuat() 함수를 이용하여 회전행렬을 회전값으로 변환해줌.
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		State->GetInfo().AttackDistance / 2.f,
		50.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);

#endif // ENABLE_DRAW_DEBUG
	//충돌이 되었을때
	if (CollisionEnable)
	{

		int32 Count = CollisionResult.Num();

		for (int32 i = 0; i < Count; i++)
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			CollisionResult[i].GetActor()->TakeDamage(
				State->mPlayerInfo.AttackPoint,
				FDamageEvent(),
				GetController(),
				this);

			AEffectCascade* Particle = GetWorld()->SpawnActor<AEffectCascade>(
				CollisionResult[i].ImpactPoint,
				CollisionResult[i].ImpactPoint.Rotation(),
				SpawnParam);

			Particle->SetSound(TEXT("SoundWave'/Game/Sound/Sound/HitSound.HitSound'"));
			Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonCountess/FX/Particles/Abilities/BladeSiphon/FX/p_Countess_BladeSiphon_HitFX.p_Countess_BladeSiphon_HitFX'"));
			
		}
	}
}

void AKnightCharacter::Skill1()
{
	PrintViewport(1.f, FColor::Red, "Skill1");

	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	if(State->mPlayerInfo.MP >=10)
	{
		int32 SkillNum = -1;

		int Count = mSkillInfoArr.Num();

		for (int32 i = 0; i < Count; i++)
		{
			if (mSkillInfoArr[i].SlotNum == 0)
			{
				SkillNum = mSkillInfoArr[i].SkillNum;
				break;
			}
		}

		if (SkillNum == -1)
			return;

		mAnimInst->UseSkill(SkillNum);


		ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();

		State->mPlayerInfo.MP -= 10;

		float Ratio = State->mPlayerInfo.MP * 0.01;

		CharacterHUD->SetMP(Ratio);
	}

}

//Skill2 : 토글방식 -> 키를 누를때와 땔때 입력이 다름
//Skill2() : 입력 시
void AKnightCharacter::Skill2()
{
	PrintViewport(1.f, FColor::Red, "Skill2");

	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	//mp가 20이하면 스킬 사용 x
	if (State->mPlayerInfo.MP >= 20)
	{
		ARBPlayerController* PlayerController = Cast<ARBPlayerController>(GetController());

		PlayerController->Skill2MousePick();
	}


}

//Skill2() : 땔 시
////mp가 20이상일 시 스킬 사용하고 mp소모
void AKnightCharacter::Skill2Released()
{
	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	if (State->mPlayerInfo.MP >= 20)
	{
		ARBPlayerController* PlayerController = Cast<ARBPlayerController>(GetController());

		PlayerController->Skill2Meteor();

		ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();

		State->mPlayerInfo.MP -= 20;

		float Ratio = State->mPlayerInfo.MP * 0.01;

		CharacterHUD->SetMP(Ratio);
	}
	
}

void AKnightCharacter::Skill3()
{
	PrintViewport(1.f, FColor::Red, "Skill3");

}

void AKnightCharacter::UseSkill(int32 SkillNum)
{
	int32 Count = mSkillInfoArr.Num();

	for (int32 i = 0; i < Count; i++)
	{
		if (mSkillInfoArr[i].SkillNum == SkillNum)
		{
			
			FActorSpawnParameters SpawnParam;

			SpawnParam.Template = mSkillInfoArr[i].SkillActor;
			SpawnParam.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ASkillProjectile* Skill =
				GetWorld()->SpawnActor<ASkillProjectile>(
					GetActorLocation() + GetActorForwardVector() * 100.f,
					GetActorRotation(),
					SpawnParam);
		}
	}
}

void AKnightCharacter::SavePlayer()
{
	Super::SavePlayer();
}

void AKnightCharacter::Skill1End(ASkillActor* SkillActor, const FHitResult& Hit)
{
	SkillActor->Destroy();
}

void AKnightCharacter::Skill2End(ASkillActor* SkillActor, const FHitResult& Hit)
{
	SkillActor->Destroy();
}


