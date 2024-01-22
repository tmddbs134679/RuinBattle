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
	//	// wŰ�� ���� ���¿��� a, d�� ���� ����.
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(0.f);

	//	// wŰ�� ���� ���¿��� ���������� �̵�.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(45.f);

	//	// wŰ�� ���� ���¿��� �������� �̵�.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-45.f);
	//}

	//else if (mDir == -1.f)
	//{
	//	// sŰ�� ���� ���¿��� a, d�� ���� ����.
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(175.f);

	//	// sŰ�� ���� ���¿��� ���������� �̵�.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(135.f);

	//	// sŰ�� ���� ���¿��� �������� �̵�.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-135.f);
	//}

	//else
	//{
	//	// �ƹ� Ű�� ������ ���� ���
	//	if (Scale == 0.f)
	//		mAnimInst->SetDir(0.f);

	//	// ���������� �̵�.
	//	else if (Scale == 1.f)
	//		mAnimInst->SetDir(90.f);

	//	// �������� �̵�.
	//	else if (Scale == -1.f)
	//		mAnimInst->SetDir(-90.f);
	//}

	//if (Scale == 0.f)
	//	return;

	AddMovementInput(GetActorRightVector(), Scale);
}
	