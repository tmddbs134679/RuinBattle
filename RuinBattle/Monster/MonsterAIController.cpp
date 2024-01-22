// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{
}

void AMonsterAIController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (IsValid(mAIBT) && IsValid(mAIBB))
	{
		UBlackboardComponent* BBComponent = Blackboard;
		if (UseBlackboard(mAIBB, BBComponent))
		{
			RunBehaviorTree(mAIBT);
		}
	}

}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterAIController::SetBehaviorTree(const FString& Path)
{
	mAIBT = LoadObject<UBehaviorTree>(nullptr, *Path);
}

void AMonsterAIController::SetBlackboard(const FString& Path)
{
	mAIBB = LoadObject<UBlackboardData>(nullptr, *Path);
}

