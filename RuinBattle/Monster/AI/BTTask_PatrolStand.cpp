// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolStand.h"
#include "../MonsterAniminstance.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTask_PatrolStand::UBTTask_PatrolStand()
{
	NodeName = TEXT("PatrolStand");
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	mWaitTime = 2.f;

}

EBTNodeResult::Type UBTTask_PatrolStand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!IsValid(Monster))
		return EBTNodeResult::Failed;


	UMonsterAniminstance* MonsterAnim = Monster->GetMonsterAnimInst();


	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (IsValid(Target))
	{
		return EBTNodeResult::Succeeded;
	}

	MonsterAnim->ChangeAnim(EMonsterAnimType::Idle);
	Controller->StopMovement();

	// 몬스터가 타겟에 도착할때까지 이 태스크를 빠져나가지 못하게한다.
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_PatrolStand::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Type();
}

void UBTTask_PatrolStand::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());


	if (!IsValid(Controller))
	{	//Failed : Task 종료
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

	if (IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	Monster->AddPatrolWaitTime(DeltaSeconds);

	if (Monster->GetPartrolWaitTime() >= mWaitTime)
	{
		Monster->ClearPatrolWaitTime();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}


}

void UBTTask_PatrolStand::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}
