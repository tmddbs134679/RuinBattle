// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemGold.h"
#include "../Inventory/Inventory.h"
#include "../UMG/InventoryBase.h"
#include "../Player/PlayerCharacter.h"
#include "../UMG/ItemDataBase.h"
#include "../RBGameInstance.h"


AItemGold::AItemGold()
{
	mItemTableRowName = TEXT("Gold");

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, 30.f));
	mMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));


	SetMesh(TEXT("StaticMesh'/Game/Megascans/3D_Assets/Orange_Brick_tj0kagyjw/SM_GoldBar.SM_GoldBar'"));




}
