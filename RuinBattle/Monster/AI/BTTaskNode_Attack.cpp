// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "../MonsterAniminstance.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	 AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	 if (!IsValid(Controller))
		 return EBTNodeResult::Failed;

	 AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	 if(!IsValid(Monster))
		 return EBTNodeResult::Failed;

	 UMonsterAniminstance* MonsterAnim = Monster->GetMonsterAnimInst();

	 //
	 AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	 
	 if (!IsValid(Target))
	 {
		 Controller->StopMovement();

		 MonsterAnim->ChangeAnim(EMonsterAnimType::Idle);

		 return EBTNodeResult::Failed;
	 }


	 MonsterAnim->ChangeAnim(EMonsterAnimType::Attack);

	 Controller->StopMovement();

	 return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskNode_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);
	return Result;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
	if(!IsValid(Monster))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UMonsterAniminstance* MonsterAnim = Monster->GetMonsterAnimInst();

	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		Controller->StopMovement();

		MonsterAnim->ChangeAnim(EMonsterAnimType::Idle);

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (Monster->GetMonsterAttackEnd())
	{
		const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

		FVector MonsterLocation = Monster->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();


		MonsterLocation = MonsterLocation - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		TargetLocation = TargetLocation - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

		float Distance = FVector::Distance(MonsterLocation, TargetLocation);

		//캡슐거리 제외
		Distance -= Monster->GetCapsuleComponent()->GetScaledCapsuleRadius();
		Distance -= Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

		if(Distance > MonsterInfo.AttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			FVector Dir = TargetLocation - MonsterLocation;
			//Z축은 의미가 없으므로 0
			Dir.Z = 0.f;
			//백터를 정규화  Normarlize : 백터 정규화 함수.
			Dir.Normalize();

			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}
		Monster->SetMonsterAttackEnd(false);
	}

}

void UBTTaskNode_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}


