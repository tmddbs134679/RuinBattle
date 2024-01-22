// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "RBPlayerState.h"
#include "RBPlayerController.h"
#include "PlayerAniminstance.h"

AArcherCharacter::AArcherCharacter()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KnightAsset(TEXT("SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Skins/Rogue/Meshes/Sparrow_Rogue.Sparrow_Rogue'"));

	if (KnightAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(KnightAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("AnimBlueprint'/Game/Player/Animation/ABArcherCharacter.ABArcherCharacter_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
}

void AArcherCharacter::BeginPlay()
{
}

void AArcherCharacter::Tick(float DeltaTime)
{
}

void AArcherCharacter::NormalAttackCheck()
{
}

void AArcherCharacter::Skill1()
{
}

void AArcherCharacter::Skill2()
{
}

void AArcherCharacter::Skill3()
{
}

void AArcherCharacter::UseSkill(int32 SkillNum)
{
}

void AArcherCharacter::MoveSide(float Scale)
{
	//if (mDir == 1.f)
	//{
	//	// w키를 누른 상태에서 a, d는 없는 상태.
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(0.f);

	//	// w키를 누른 상태에서 오른쪽으로 이동.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(45.f);

	//	// w키를 누른 상태에서 왼쪽으로 이동.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-45.f);
	//}

	//else if (mDir == -1.f)
	//{
	//	// s키를 누른 상태에서 a, d는 없는 상태.
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(175.f);

	//	// s키를 누른 상태에서 오른쪽으로 이동.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(135.f);

	//	// s키를 누른 상태에서 왼쪽으로 이동.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-135.f);
	//}

	//else
	//{
	//	// 아무 키도 누른게 없을 경우
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(0.f);

	//	// 오른쪽으로 이동.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(90.f);

	//	// 왼쪽으로 이동.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-90.f);
	//}

	//if (Scale == 0.f)
	//	return;

	AddMovementInput(GetActorRightVector(), Scale);
}
	