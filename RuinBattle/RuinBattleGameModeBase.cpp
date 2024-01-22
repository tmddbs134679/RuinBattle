// Copyright Epic Games, Inc. All Rights Reserved.


#include "RuinBattleGameModeBase.h"
#include "Player/RBPlayerState.h"
#include "Player/RBPlayerController.h"
#include "Player/KnightCharacter.h"
#include "Player/ArcherCharacter.h"
#include "RBGameInstance.h"
#include "RBSaveGame.h"

ARuinBattleGameModeBase::ARuinBattleGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerStateClass = AKnightCharacter::StaticClass();
	//PlayerStateClass = AArcherCharacter::StaticClass();
	PlayerStateClass = ARBPlayerState::StaticClass();
	PlayerControllerClass = ARBPlayerController::StaticClass();
	DefaultPawnClass = AKnightCharacter::StaticClass();

	ConstructorHelpers::FClassFinder<UUserWidget> FinderCharacterHUD(TEXT("WidgetBlueprint'/Game/Blueprint/UMG/UI_CharacterHUD.UI_CharacterHUD_C'"));

	if (FinderCharacterHUD.Succeeded())
	{
		mCharacterHUDClass = FinderCharacterHUD.Class;
	}
}

//호출순서 InitGame -> PostLogin -> BeginPlay 

void ARuinBattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	mSaveGame = NewObject<URBSaveGame>();

	mCharacterHUD = Cast<UCharacterHUDBase>(CreateWidget(GetWorld(), mCharacterHUDClass));

	if (IsValid(mCharacterHUDClass))
	{
		mCharacterHUD->AddToViewport();
	}
}

void ARuinBattleGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARuinBattleGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//URBGameInstance* GameInstance = GetWorld()->GetGameInstance<URBGameInstance>();


}

void ARuinBattleGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed:
		LOG(TEXT("Destroyed"));
		break;
	case EEndPlayReason::LevelTransition:
		LOG(TEXT("Level Transition"));
		SaveGame();
	/*		APlayerCharacter* PlayerCharacter;

		PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (IsValid(PlayerCharacter))
			PlayerCharacter->SavePlayer()*/;

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

void ARuinBattleGameModeBase::SaveGame()
{
	//UGameplayStatics::SaveGameToSlot(mSaveGame, TEXT("Save"), 0);

	//메모리 데이터 직렬화
	FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGame/Save.txt");


	FArchive* Writer = IFileManager::Get().CreateFileWriter(*FullPath);
	if (Writer)
	{
		*Writer << mSaveGame->mPlayerInfo.Name;
		*Writer << mSaveGame->mPlayerInfo.Job;
		*Writer << mSaveGame->mPlayerInfo.AttackPoint;
		*Writer << mSaveGame->mPlayerInfo.HP;
		*Writer << mSaveGame->mPlayerInfo.HPMax;
		*Writer << mSaveGame->mPlayerInfo.MP;
		*Writer << mSaveGame->mPlayerInfo.MPMax;
		*Writer << mSaveGame->mPlayerInfo.Level;
		*Writer << mSaveGame->mPlayerInfo.Exp;
		*Writer << mSaveGame->mPlayerInfo.Gold;
		*Writer << mSaveGame->mPlayerInfo.MoveSpeed;
		*Writer << mSaveGame->mPlayerInfo.AttackDistance;
		*Writer << mSaveGame->mZoomMax;
		*Writer << mSaveGame->mZoomMin;

		Writer->Close();

		delete Writer;
	}
}
