// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "RBPlayerState.h"
#include "PlayerAniminstance.h"
#include "../RBSaveGame.h"
#include "../RuinBattleGameModeBase.h"
#include "../RBGameInstance.h"
#include "../UMG/CharacterHUDBase.h"
#include "../Monster/Monster.h"
#include "../Inventory/Inventory.h"
#include "../PostProcess/RBPostProcessVolume.h"
#include "../UMG/ExplanationBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	
	mSpringArm->SetupAttachment(GetMesh());
	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 1000.f;
	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 170.0));
	mSpringArm->SetRelativeRotation(FRotator(-50.0, 90.0, 0.0));
	//마우스 컨트롤 기능
	mSpringArm->bUsePawnControlRotation = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCharacterMovement()->JumpZVelocity = 600.f;

	mDir = 0.f;


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	UInventory::GetInst(GetWorld())->ShowInventory(false);

	mAnimInst = Cast<UPlayerAniminstance>(GetMesh()->GetAnimInstance());

	//load 방법  = slot, memory
	//URBSaveGame* LoadGame = Cast<URBSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save"),0));

	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	URBGameInstance* GameInstance =
		GetWorld()->GetGameInstance<URBGameInstance>();

	const FPlayerTableInfo* PlayerInfo =
		GameInstance->FindRowPlayerTable(mPlayerTableRowName);


	FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGame/Save.txt");

	TSharedPtr<FArchive>	Reader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	//Save된 데이터 가져오기.
	if (Reader.IsValid())
	{
		*Reader.Get() << State->mPlayerInfo.Name;
		*Reader.Get() << State->mPlayerInfo.Job;
		*Reader.Get() << State->mPlayerInfo.AttackPoint;
		*Reader.Get() << State->mPlayerInfo.HP;
		*Reader.Get() << State->mPlayerInfo.HPMax;
		*Reader.Get() << State->mPlayerInfo.MP;
		*Reader.Get() << State->mPlayerInfo.MPMax;
		*Reader.Get() << State->mPlayerInfo.Level;
		*Reader.Get() << State->mPlayerInfo.Exp;
		*Reader.Get() << State->mPlayerInfo.Gold;
		*Reader.Get() << State->mPlayerInfo.MoveSpeed;
		*Reader.Get() << State->mPlayerInfo.AttackDistance;
		*Reader.Get() << State->mZoomMin;
		*Reader.Get() << State->mZoomMax;
	}
	else
	{

		mPlayerInfo.Name = PlayerInfo->Name;
		mPlayerInfo.Job = PlayerInfo->Job;
		mPlayerInfo.AttackPoint = PlayerInfo->AttackPoint;
		mPlayerInfo.HP = PlayerInfo->HP;
		mPlayerInfo.HPMax = PlayerInfo->HP;
		mPlayerInfo.MP = PlayerInfo->MP;
		mPlayerInfo.MPMax = PlayerInfo->MP;
		mPlayerInfo.Level = PlayerInfo->Level;
		mPlayerInfo.Exp = PlayerInfo->Exp;
		mPlayerInfo.Gold = PlayerInfo->Gold;
		mPlayerInfo.MoveSpeed = PlayerInfo->MoveSpeed;
		

		
		State->mPlayerInfo.Name = mPlayerInfo.Name;
		State->mPlayerInfo.Job = mPlayerInfo.Job;
		State->mPlayerInfo.AttackPoint = mPlayerInfo.AttackPoint;
		State->mPlayerInfo.HP = mPlayerInfo.HP;
		State->mPlayerInfo.HPMax = mPlayerInfo.HPMax;
		State->mPlayerInfo.MP = mPlayerInfo.MP;
		State->mPlayerInfo.MPMax = mPlayerInfo.MPMax;
		State->mPlayerInfo.Level = mPlayerInfo.Level;
		State->mPlayerInfo.Exp = mPlayerInfo.Exp;
		State->mPlayerInfo.Gold = mPlayerInfo.Gold;
		State->mPlayerInfo.MoveSpeed = mPlayerInfo.MoveSpeed;
	}

	 float RatioHP = State->mPlayerInfo.HP * 0.01;
	 float RatioMP = State->mPlayerInfo.MP * 0.01 ;
	 int Level = State->mPlayerInfo.Level;

	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();

	CharacterHUD->SetHP(RatioHP);
	CharacterHUD->SetMP(RatioMP);
	CharacterHUD->SetLevel(Level);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//액션 바인딩
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("NormalAttack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::NormalAttack);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SprintKey);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::SprintKeyOff);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill1"), EInputEvent::IE_Released, this, &APlayerCharacter::Skill1Key);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill2"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Skill2Key);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill2"), EInputEvent::IE_Released, this, &APlayerCharacter::Skill2KeyReleased);
	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Skill3"), EInputEvent::IE_Released, this, &APlayerCharacter::Skill3Key);

	FInputActionBinding& toggle = PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &APlayerCharacter::InventoryOn);

	PlayerInputComponent->BindAction<APlayerCharacter>(TEXT("Explanation"), EInputEvent::IE_Released, this, &APlayerCharacter::Explanation);

	//축 바인딩
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("MoveSide"), this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoom);

}

void APlayerCharacter::NormalAttackCheck()
{
}

void APlayerCharacter::NormalAttack()
{
	mAnimInst->Attack();
}

void APlayerCharacter::JumpKey()
{
	Jump();
	mAnimInst->Jump();
}

void APlayerCharacter::SprintKey()
{

	mAnimInst->Sprint();
}

void APlayerCharacter::SprintKeyOff()
{
	mAnimInst->SprintOff();

}

void APlayerCharacter::Skill1Key()
{
	Skill1();
}

void APlayerCharacter::Skill2Key()
{
	Skill2();
}

void APlayerCharacter::Skill2KeyReleased()
{
	Skill2Released();
}

void APlayerCharacter::Skill3Key()
{
	Skill3();
}

void APlayerCharacter::InventoryOn()
{
	PrintViewport(1.f, FColor::Red, TEXT("Inventory On"));

	UInventory::GetInst(GetWorld())->ShowInventory(true);
}

void APlayerCharacter::MoveForward(float Scale)
{
	mDir = Scale;

	if (Scale == 0.f)
		return;

	AddMovementInput(GetActorForwardVector(), Scale);
}

void APlayerCharacter::MoveSide(float Scale)
{
	if (mDir == 1.f)
	{
		// w키를 누른 상태에서 a, d는 없는 상태.
		if (Scale == 0.f)
			mAnimInst->SetDir(0.f);

		// w키를 누른 상태에서 오른쪽으로 이동.
		else if (Scale == 1.f)
			mAnimInst->SetDir(45.f);

		// w키를 누른 상태에서 왼쪽으로 이동.
		else if (Scale == -1.f)
			mAnimInst->SetDir(-45.f);
	}

	else if (mDir == -1.f)
	{
		// s키를 누른 상태에서 a, d는 없는 상태.
		if (Scale == 0.f)
			mAnimInst->SetDir(180.f);

		// s키를 누른 상태에서 오른쪽으로 이동.
		else if (Scale == 1.f)
			mAnimInst->SetDir(135.f);

		// s키를 누른 상태에서 왼쪽으로 이동.
		else if (Scale == -1.f)
			mAnimInst->SetDir(-135.f);
	}

	else
	{
		// 아무 키도 누른게 없을 경우
		if (Scale == 0.f)
			mAnimInst->SetDir(0.f);

		// 오른쪽으로 이동.
		else if (Scale == 1.f)
			mAnimInst->SetDir(90.f);

		// 왼쪽으로 이동.
		else if (Scale == -1.f)
			mAnimInst->SetDir(-90.f);
	}

	if (Scale == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), Scale);
}

void APlayerCharacter::Turn(float Scale)
{
	//Z축 회전(Yaw)
	if (Scale == 0.f)
		return;

	AddControllerYawInput(Scale * 180.f * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUp(float Scale)
{
	//Y축회전(Pitch)
	if (Scale == 0.f)
		return;

	AddControllerPitchInput(Scale);
}

void APlayerCharacter::CameraZoom(float Scale)
{
	if (Scale == 0.f)
		return;
	//70.f씩 줌아웃
	mSpringArm->TargetArmLength += Scale * 70.f;
	
	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	float ZoomMin = 800.f;
	float ZoomMax = 1200.f;

	if (IsValid(State))
	{
		ZoomMin = State->GetZoomMin();
		ZoomMax = State->GetZoomMax();
	}

	if (ZoomMin > mSpringArm->TargetArmLength)
		mSpringArm->TargetArmLength = ZoomMin;

	else if (ZoomMax < mSpringArm->TargetArmLength)
		mSpringArm->TargetArmLength = ZoomMax;
}

void APlayerCharacter::GetExp(int Exp)
{
	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());


	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();

	State->mPlayerInfo.Exp += Exp;

	if (State->mPlayerInfo.Exp >= 100)
	{
		++State->mPlayerInfo.Level;

		CharacterHUD->SetLevel(State->mPlayerInfo.Level);
		State->mPlayerInfo.Exp -= 100;
	}


}

void APlayerCharacter::Explanation()
{
	PrintViewport(1.f, FColor::Red, TEXT("Explanation"));

	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//main level 아닐경우 예외처리
	if (GameMode == nullptr)
		return;

	UCharacterHUDBase* MainHUD = GameMode->GetCharacterHUD();

	UExplanationBase* ExplanationWidget = MainHUD->GetExplanationWidget();

	ExplanationWidget->ShowExplanation();
}



void APlayerCharacter::Skill1()
{

}

void APlayerCharacter::Skill2()
{
}

void APlayerCharacter::Skill2Released()
{
}

void APlayerCharacter::Skill3()
{
}

void APlayerCharacter::UseSkill(int32 SkillNum)
{
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());

	//FLinearColor Color;
	//float Invensity;
	//ARBPostProcessVolume* ProcessVolume = Cast<ARBPostProcessVolume>();

	if (IsValid(State))
	{
		if (State->mPlayerInfo.HP <= 10)
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			mAnimInst->ChangeAnim(EPlayerAnimType::Death);

		}
		State->mPlayerInfo.HP -= Damage;

		Damage = Damage < 1 ? 1 : Damage;

	}
	
	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();


	static float Ratio = State->mPlayerInfo.HP * 0.01 + 0.1;

	//static float Ratio = (float)State->mPlayerInfo.HP / (float)State->mPlayerInfo.HPMax;

	Ratio -= ((Damage) * 0.01);
	
	CharacterHUD->SetHP(Ratio);

	return Damage;
}

void APlayerCharacter::SavePlayer()
{
	URBSaveGame* SaveGame = NewObject<URBSaveGame>();

	ARBPlayerState* State = Cast<ARBPlayerState>(GetPlayerState());
	

	URBGameInstance* GameInstance =
		GetWorld()->GetGameInstance<URBGameInstance>();


	SaveGame->mPlayerInfo = State->mPlayerInfo;
	SaveGame->mZoomMin = State->mZoomMin;
	SaveGame->mZoomMax = State->mZoomMax;


	const FPlayerTableInfo* PlayerInfo =
		GameInstance->FindRowPlayerTable(mPlayerTableRowName);


	//SaveGame->mPlayerInfo.AttackDistance = PlayerInfo->AttackDistance;
	//SaveGame->mPlayerInfo.AttackPoint = PlayerInfo->AttackPoint;
	//SaveGame->mPlayerInfo.Exp = PlayerInfo->Exp;
	//SaveGame->mPlayerInfo.Gold = PlayerInfo->Gold;
	//SaveGame->mPlayerInfo.HP = PlayerInfo->HP;
	//SaveGame->mPlayerInfo.Job = PlayerInfo->Job;
	//SaveGame->mPlayerInfo.Level = PlayerInfo->Level;
	//SaveGame->mPlayerInfo.MoveSpeed = PlayerInfo->MoveSpeed;
	//SaveGame->mPlayerInfo.MP = PlayerInfo->MP;
	//SaveGame->mPlayerInfo.Name = PlayerInfo->Name;

	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Save"), 0);
}



void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//SavePlayer();

	LOG(TEXT("EndPlay"));

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed:
		LOG(TEXT("Destroyed"));
		break;
	case EEndPlayReason::LevelTransition:
		LOG(TEXT("Level Transition"));
		break;
	case EEndPlayReason::EndPlayInEditor:
		LOG(TEXT("EndPlayInEditor"));
		break;
	case EEndPlayReason::RemovedFromWorld:
		LOG(TEXT("RemovedFromWorld"));
		break;
	case EEndPlayReason::Quit:
		LOG(TEXT("Quit"));
		break;
	}
}
