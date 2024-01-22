// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemDataBase.generated.h"

/**
 TileView�� �־��� ���ڸ� ������ִ� Ŭ���� �Դϴ�.
 TileVIew�� �ְ���� ���ڸ� Setting
 */
UCLASS()
class RUINBATTLE_API UItemDataBase : public UObject
{
	GENERATED_BODY()

public:
	UItemDataBase();
	~UItemDataBase();

public:

	void SetIconPath(const FString& _IconPath) 
	{ 
		mIconPath = _IconPath;
	}

	void SetItemCount(int _Count) 
	{
		mItemCount = _Count;
	}

	void SetItemName(const FString& _String)
	{
		mItemName = _String;
	}

public:

	const FString& GetIconPath()
	{ 
		return mIconPath;
	}

	const FString& GetItemName()
	{
		return mItemName;
	}


	int GetItemCount() 
	{
		return mItemCount; 
	}

private:
	
	FString mItemName;
	FString	mIconPath;
	int		mItemCount;



	
};
