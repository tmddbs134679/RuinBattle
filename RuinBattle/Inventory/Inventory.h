// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/**
 ���� Inventory ����
 */
UCLASS()
class RUINBATTLE_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory();
	~UInventory();

public:
	bool IsInventoryOpen();
	void SetItemTable(UDataTable* Table);
	//const FItemDataInfo* GetItemInfo(EITEM_ID ItemID);
	static UInventory* GetInst(UWorld* World);
	const FItemDataInfo* FindItemTable(const FName& Name);
	const FItemDataInfo* GetItemInfo(EITEM_ID _ItemID);

	
public:
	//�������Ʈ���� ��밡��
	UFUNCTION(BlueprintCallable)

	static UInventory* GetInst(UGameInstance* GameInst);

	UFUNCTION(BlueprintCallable)
		
	void ShowInventory(bool On);



public:
	UDataTable* mItemTable;

	TMap<EITEM_ID, FName>	mRownameFromID;


	int32	mPrevSeconds;

private:

	static UWorld* mWorld;


};
