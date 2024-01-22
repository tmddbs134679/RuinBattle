// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API UMonsterAniminstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAniminstance();

public:

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:
	void ChangeAnim(EMonsterAnimType Anim)
	{
		mAnimType = Anim;
	}
	
	void Hit()
	{
		if (!IsValid(mHitMontage))
			return;

		mHitAdditive = 1.f;

		if (!Montage_IsPlaying(mHitMontage))
		{
			Montage_SetPosition(mHitMontage, 0.f);
			Montage_IsPlaying(mHitMontage);
		}
	}


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EMonsterAnimType	mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mHitAdditive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAnimMontage* mHitMontage;
public:
	UFUNCTION()
		void AnimNotify_DeathEnd();

	UFUNCTION()
		void AnimNotify_HitEnd();

	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_HitBackEnd();

};
