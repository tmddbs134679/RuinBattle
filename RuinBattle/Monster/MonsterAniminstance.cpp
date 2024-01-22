// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAniminstance.h"
#include "Monster.h"
#include "../Effect/EffectNiagara.h"
#include "../Item/ItemGold.h"

UMonsterAniminstance::UMonsterAniminstance()
{
	mAnimType = EMonsterAnimType::Idle;
	mHitAdditive = 0;
}

void UMonsterAniminstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAniminstance::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	FVector MLocation = Monster->GetActorLocation();
	FRotator MRotator = Monster->GetActorRotation();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AItemGold* Item = GetWorld()->SpawnActor<AItemGold>(
		MLocation,
		MRotator,
		SpawnParam);

	

}

void UMonsterAniminstance::AnimNotify_HitEnd()
{
	mHitAdditive = 0;
}

void UMonsterAniminstance::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
	{
		Monster->Attack();
	}
}

void UMonsterAniminstance::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->SetMonsterAttackEnd(true);
}

void UMonsterAniminstance::AnimNotify_HitBackEnd()
{

}
