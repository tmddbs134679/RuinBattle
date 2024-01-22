// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTDecorator_CheckDistance::UBTDecorator_CheckDistance()
{
}

bool UBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Controller =
		Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
		return false;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!IsValid(Monster))
		return false;

	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
		return false;

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();


	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();


	MonsterLocation = MonsterLocation - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLocation = TargetLocation -FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	float Distance = FVector::Distance(MonsterLocation, TargetLocation);

	//Ä¸½¶°Å¸® Á¦¿Ü
	Distance -= Monster->GetCapsuleComponent()->GetScaledCapsuleRadius();
	Distance -= Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

	float Type = 0.f;

	switch (mDistanceType)
	{
	case EDistanceType::Attack:
		Type = MonsterInfo.AttackDistance;
		break;
	case EDistanceType::Trace:
		Type = MonsterInfo.TraceDistance;
		break;
	}

	return	Distance <= Type;
}
