// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../GameInfo.h"
#include <Components/TileView.h>

#include "ItemDataBase.h"
#include "Blueprint/UserWidget.h"
#include "InventoryBase.generated.h"


/**
 * 
 */
UCLASS()
class RUINBATTLE_API UInventoryBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	UTileView* GetTileView()
	{
		return mTileView;
	}
	
	

private:
	UTileView* mTileView;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName	mItemDataInfoRowName;

	
	

};
