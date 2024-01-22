// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UMG/CharacterHUDBase.h"
#include "UMG/ExplanationBase.h"
#include "GameFramework/GameModeBase.h"
#include "RuinBattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API ARuinBattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARuinBattleGameModeBase();

public:
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);


private:
	void SaveGame();

public:
	UCharacterHUDBase* GetCharacterHUD()
	{
		return mCharacterHUD;
	}


	class URBSaveGame* GetSaveGame()
	{
		return mSaveGame;
	}

private:
	UCharacterHUDBase* mCharacterHUD;

	
	TSubclassOf<UUserWidget>	mCharacterHUDClass;

	class URBSaveGame* mSaveGame;
};
