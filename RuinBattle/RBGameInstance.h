// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



class UInventory;

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "RBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API URBGameInstance : public UGameInstance
{
	GENERATED_BODY()

		

public:
	URBGameInstance();
	~URBGameInstance();

	

public:
	virtual void Init();

	friend class UInventory;

public:

	const FMonsterTableInfo* FindRowMonsterTable(const FName& Name);
	const FPlayerTableInfo* FindRowPlayerTable(const FName& Name);

	const FSkillData* FindRowMonsterSkillTable(const FName& Name);

private:

	UDataTable* mMonsterTable;
	UDataTable* mPlayerTable;
	UDataTable* mItemTable;


	UDataTable* mMonsterSkillTable;

	UInventory* mInventory;

	
};
