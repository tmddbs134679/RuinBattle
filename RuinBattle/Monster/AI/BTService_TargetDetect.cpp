// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TargetDetect.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTService_TargetDetect::UBTService_TargetDetect()
{
	NodeName = TEXT("TargetDetect");
	Interval = 0.5;
	RandomDeviation = 0.3;

}

void UBTService_TargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if(!IsValid(Controller))
		return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!IsValid(Monster))
		return;


	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();
	FCollisionQueryParams param(NAME_None, false, Monster);
	TArray<FOverlapResult> OverlapResult;

	bool CollisionEnable = GetWorld()->OverlapMultiByChannel(
		OverlapResult,
		Monster->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(MonsterInfo.TraceDistance),
		param);

//확인용 감지 구체 생성
#if ENABLE_DRAW_DEBUG

	
	FColor	DrawColor = CollisionEnable ? FColor::Black : FColor::Yellow;


	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(),
		MonsterInfo.TraceDistance, 20,
		DrawColor, false, 0.5f);

#endif

	if (CollisionEnable)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), OverlapResult[0].GetActor());

		Monster->GetWidgetComponent()->SetVisibility(true, false);

	}
	else
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
}
