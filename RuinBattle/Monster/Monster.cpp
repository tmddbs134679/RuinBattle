// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "MonsterAIController.h"
#include "../RBGameInstance.h"
#include "../UMG/MonsterHPBase.h"
#include "../Player/PlayerCharacter.h"

// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);

	// CanCharacterStepUpOn  : 캐릭터 위에 올라갈 수 있냐 없냐.
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterAIController::StaticClass();

	mAttackEnd = false;

	mPatrolIndex = 1;
	mPatrolIndexAdd = 1;
	mPatrolWaitTime = 0.f;

	mWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGETCOMPONENT"));
	mWidgetComponent->SetupAttachment(GetMesh());


}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	
	URBGameInstance* GameInstance =
		GetWorld()->GetGameInstance<URBGameInstance>();

	const FMonsterTableInfo* MonsterInfo = 
		GameInstance->FindRowMonsterTable(mMonsterTableRowName);
										   
	if (MonsterInfo)
	{
		mMonsterInfo.Name = MonsterInfo->Name;
		mMonsterInfo.AttackDistance = MonsterInfo->AttackDistance;
		mMonsterInfo.AttackPoint = MonsterInfo->AttackPoint;
		mMonsterInfo.HP = MonsterInfo->HP;
		mMonsterInfo.HPMax = MonsterInfo->HP;
		mMonsterInfo.MP = MonsterInfo->MP;
		mMonsterInfo.Level = MonsterInfo->Level;
		mMonsterInfo.Exp = MonsterInfo->Exp;
		mMonsterInfo.Gold = MonsterInfo->Gold;
		mMonsterInfo.MoveSpeed = MonsterInfo->MoveSpeed;
		mMonsterInfo.AttackDistance = MonsterInfo->AttackDistance;
		mMonsterInfo.TraceDistance = MonsterInfo->TraceDistance;
	}

	mAnimInst = Cast<UMonsterAniminstance>(GetMesh()->GetAnimInstance());


	UMonsterHPBase* MonsterHPWidget = Cast<UMonsterHPBase>(mWidgetComponent->GetWidget());

	if (IsValid(MonsterHPWidget))
	{
		MonsterHPWidget->SetInitHP(mMonsterInfo.HP);
	}
	mWidgetComponent->SetVisibility(false, false);



}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 Damage = (int32)Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage = Damage < 1 ? 1 : Damage;

	mMonsterInfo.HP -= Damage;
	
	float MonsterRatio = mMonsterInfo.HP * 0.01;

	UMonsterHPBase* MonsterHPWidget = Cast<UMonsterHPBase>(mWidgetComponent->GetWidget());

	//처음 TakeDamage 받을 때 켜지면서 몬스터 정보 초기화 해주고 SetHP
	if (IsValid(MonsterHPWidget))
	{
		MonsterHPWidget->SetInitHP(MonsterRatio);

		MonsterHPWidget->SetHP(MonsterRatio);
	}

	mWidgetComponent->SetVisibility(true, false);

	if (mMonsterInfo.HP <= 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		mAnimInst->ChangeAnim(EMonsterAnimType::Death);

		AAIController* AI = Cast<AAIController>(GetController());

		if (IsValid(AI))
			AI->BrainComponent->StopLogic(TEXT("Death"));

		mWidgetComponent->DestroyComponent();

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		PlayerCharacter->GetExp(40);

	}
	else
	{
		mAnimInst->Hit();
	}
	
	return Damage;
}

void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMonsterAIController* AIController = Cast<AMonsterAIController>(NewController);

	if (IsValid(AIController))
	{
		AIController->SetBehaviorTree(TEXT("BehaviorTree'/Game/Monster/AI/BTMonster.BTMonster'"));
		AIController->SetBlackboard(TEXT("BlackboardData'/Game/Monster/AI/BBMonster.BBMonster'"));
	}
}

void AMonster::UnPossessed()
{
	Super::UnPossessed();
}

void AMonster::Attack()
{
}

void AMonster::LevelStartAI()
{
	AAIController* AI = Cast<AAIController>(GetController());


	//BrainComponent : responsible for behaviors
	if (IsValid(AI))
		AI->BrainComponent->StartLogic();


}


