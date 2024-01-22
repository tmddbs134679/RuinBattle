// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TargetTrace.h"
#include "../MonsterAniminstance.h"
#include "../MonsterAIController.h"
#include "../Monster.h"


UBTTaskNode_TargetTrace::UBTTaskNode_TargetTrace()
{
	NodeName = TEXT("TargetTrace");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTaskNode_TargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	if (!IsValid(Target))
	{
		Controller->StopMovement();

		MonsterAnim->ChangeAnim(EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}
	
	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	Monster->GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;

	//AI이동함수
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	MonsterAnim->ChangeAnim(EMonsterAnimType::CombatRun);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskNode_TargetTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
}

void UBTTaskNode_TargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());


	if (!IsValid(Controller))
	{	//Failed : Task 종료
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());
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

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();


	FVector MonsterLocation = Monster->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	MonsterLocation = MonsterLocation - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLocation = TargetLocation - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	float Distance = FVector::Distance(MonsterLocation, TargetLocation);

	//캡슐거리 제외
	Distance -= Monster->GetCapsuleComponent()->GetScaledCapsuleRadius();
	Distance -= Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

	//공격 거리에 진입
	if (Distance <= MonsterInfo.AttackDistance)
	{
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	

}

void UBTTaskNode_TargetTrace::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
