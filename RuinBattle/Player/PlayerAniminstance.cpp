// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAniminstance.h"
#include "PlayerCharacter.h"

UPlayerAniminstance::UPlayerAniminstance()
{
	mDir = 0.f;
	mAttackEnable = true;
	mAttack = false;
	mAttackIndex= 0;

	mAnimType = EPlayerAnimType::Ground;

	mGround = true;
	mFallRecoveryAdditive = 0.f;

	mUseSkillNum = -1;
}

void UPlayerAniminstance::Attack()
{
	//PrintViewport(1.f, FColor::Red, TEXT("AttackIn"));
	
	if (!mAttackEnable)
		return;

	mAttackEnable = false;

	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{

		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		//공격속도 조절가능
		Montage_Play(mAttackMontageArray[mAttackIndex]);

		//0123반복하게 mAttackMontageArray.Num() 나머지
		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
		mAttack = true;
	}
	else
		mAttackEnable = true;


}

void UPlayerAniminstance::Jump()
{
	mAnimType = EPlayerAnimType::Jump;
}

void UPlayerAniminstance::Sprint()
{
	mAnimType = EPlayerAnimType::Sprint;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movemont = PlayerCharacter->GetCharacterMovement();

		Movemont->MaxWalkSpeed = 2000.f;
	}
}

void UPlayerAniminstance::SprintOff()
{
	mAnimType = EPlayerAnimType::Ground;


	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	
	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movemont = PlayerCharacter->GetCharacterMovement();

		Movemont->MaxWalkSpeed = 1000.f;
		//속도저장
		mSpeedRatio = Movemont->Velocity.Size() / Movemont->MaxWalkSpeed;
	}
}

void UPlayerAniminstance::UseSkill(int32 SkillNum)
{
	PrintViewport(1.f, FColor::Red, TEXT("UseSkill"));
	int32 Count = mSkillMontageArr.Num();

	for (int32 i = 0; i < Count; ++i)
	{
		if (mSkillMontageArr[i].SkillNum == SkillNum)
		{
			mUseSkillNum = SkillNum;
			//IsPlaying 함수는 확인함수
			if (!Montage_IsPlaying(mSkillMontageArr[i].Montage))
			{
				Montage_SetPosition(mSkillMontageArr[i].Montage, 0.f);
				//Play-> 작동
				Montage_Play(mSkillMontageArr[i].Montage);
			}
			break;
		}
	}
}




void UPlayerAniminstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UPlayerAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movemont = PlayerCharacter->GetCharacterMovement();

		//속도저장
		mSpeedRatio = Movemont->Velocity.Size() / Movemont->MaxWalkSpeed;

		////땅위에 있으면 mGround true
		mGround = Movemont->IsMovingOnGround();

		if (mAnimType != EPlayerAnimType::Jump && !mGround)
		{
			mAnimType = EPlayerAnimType::Fall;
		}
	}
	
}

void UPlayerAniminstance::AnimNotify_Attack()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
		PlayerCharacter->NormalAttackCheck();
}

void UPlayerAniminstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAniminstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mAttack = false;
}

void UPlayerAniminstance::AnimNotify_JumpEnd()
{
	mAnimType = EPlayerAnimType::Fall;
}

void UPlayerAniminstance::AnimNotify_FallEnd()
{
	mAnimType = EPlayerAnimType::Ground;
	
	if (IsValid(mFallRecoveryMontage))
	{
		mFallRecoveryAdditive = 1.f;

		Montage_SetPosition(mFallRecoveryMontage, 0.f);
		Montage_Play(mFallRecoveryMontage);
	}
}

void UPlayerAniminstance::AnimNotify_FallRecoveryEnd()
{
	mFallRecoveryAdditive = 0.f;
}

void UPlayerAniminstance::AnimNotify_UseSKill()
{
	PrintViewport(1.f, FColor::Red, TEXT("ANIMUSESKILL"));
	if (mUseSkillNum == -1)
		return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
		PlayerCharacter->UseSkill(mUseSkillNum);

}

void UPlayerAniminstance::AnimNotify_DeathEnd()
{
	PrintViewport(1.f, FColor::Red, TEXT("DeathEnd"));

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	PlayerCharacter->Destroy();
}
