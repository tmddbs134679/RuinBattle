// Fill out your copyright notice in the Description page of Project Settings.


#include "RBGameInstance.h"

#include "Inventory/Inventory.h"

URBGameInstance::URBGameInstance() 
	: mMonsterTable(nullptr)
	 ,mPlayerTable(nullptr)
   	,mItemTable(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterTable(TEXT("DataTable'/Game/Monster/MonsterTableInfo.MonsterTableInfo'"));

	if (MonsterTable.Succeeded())
		mMonsterTable = MonsterTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTable(TEXT("DataTable'/Game/Player/PlayerTableInfo.PlayerTableInfo'"));

	if (PlayerTable.Succeeded())
		mPlayerTable = PlayerTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTable(TEXT("DataTable'/Game/Skill/DTMonsterSkillTable.DTMonsterSkillTable'"));

	if (MonsterInfoTable.Succeeded())
		mMonsterSkillTable = PlayerTable.Object;


	static ConstructorHelpers::FObjectFinder<UDataTable>	ItemTable(TEXT("DataTable'/Game/Item/DTItemDataTable.DTItemDataTable'"));
	if (ItemTable.Succeeded())
	{
		mItemTable = ItemTable.Object;
		UInventory::GetInst(this)->SetItemTable(mItemTable);
	}


}

URBGameInstance::~URBGameInstance()
{
}

void URBGameInstance::Init()
{
}

const FMonsterTableInfo* URBGameInstance::FindRowMonsterTable(const FName& Name)
{
	//gameinstance 세팅 해놔야함
	return mMonsterTable->
		FindRow<FMonsterTableInfo>(Name, TEXT(""));
}

const FPlayerTableInfo* URBGameInstance::FindRowPlayerTable(const FName& Name)
{
	return mPlayerTable->
		FindRow<FPlayerTableInfo>(Name, TEXT(""));
}

const FSkillData* URBGameInstance::FindRowMonsterSkillTable(const FName& Name)
{
	return mMonsterSkillTable->
		FindRow<FSkillData>(Name, TEXT(""));
}

