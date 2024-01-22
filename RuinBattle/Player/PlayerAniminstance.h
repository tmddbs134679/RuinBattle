// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAniminstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Ground,
	Sprint,
	Jump,
	Fall,
	Death
};

USTRUCT(BlueprintType)
struct FSkillAnimInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 SkillNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* Montage;

};


UCLASS()
class RUINBATTLE_API UPlayerAniminstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPlayerAniminstance();

public:
	void Attack();
	void Jump();
	void Sprint();
	void SprintOff();
	void UseSkill(int32 SkillNum);



public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:
	void SetDir(float Dir)
	{
		mDir = Dir;
	}

	EPlayerAnimType GetPlayerAnimType()	const
	{
		return mAnimType;
	}

	void ChangeAnim(EPlayerAnimType Anim)
	{
		mAnimType = Anim;
	}

public:
	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_JumpEnd();

	UFUNCTION()
		void AnimNotify_FallEnd();

	UFUNCTION()
		void AnimNotify_FallRecoveryEnd();

	UFUNCTION()
		void AnimNotify_UseSKill();

	UFUNCTION()
		void AnimNotify_DeathEnd();
protected:

	int32	mUseSkillNum;

public:



protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mSpeedRatio;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mAttackEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32	mAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*> mAttackMontageArray;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EPlayerAnimType	mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mJumpLoop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mFallRecoveryAdditive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAnimMontage* mFallRecoveryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<FSkillAnimInfo>	mSkillMontageArr;
};
