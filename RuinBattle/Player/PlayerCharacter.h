// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RUINBATTLE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void NormalAttackCheck();
public:

	//액션매핑 바인딩
	void NormalAttack();
	void JumpKey();
	void SprintKey();
	void SprintKeyOff();

	void Skill1Key();
	void Skill2Key();

	void Skill2KeyReleased();

	void Skill3Key();
	void InventoryOn();

	//축매빙 바인딩
	void MoveForward(float Scale);
	void Turn(float Scale);
	void LookUp(float Scale);
	void CameraZoom(float Scale);

	void GetExp(int Exp);

	void Explanation();



public:


	//직업이 2가지 이상이기 떄문에 오버라이딩
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill2Released();

	virtual void Skill3();
	virtual void UseSkill(int32 SkillNum);
	virtual void MoveSide(float Scale);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual void SavePlayer();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
protected:
	
	float mDir;
	class UPlayerAniminstance* mAnimInst;

	AActor* mAttackActor;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
	UCameraComponent* mCamera;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Skill, meta = (AllowPrivatedAccess = true))
	TArray<FSkillInfo>	mSkillInfoArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName				mPlayerTableRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FPlayerInfo		mPlayerInfo;

};
