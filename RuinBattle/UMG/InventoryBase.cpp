// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"
#include "../Inventory/Inventory.h"
#include "../RBGameInstance.h"


//�κ��丮 TileView�� ������ �߰�
void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();

	//TileView �׸� 1�� -> Path, Name, Count ���� ���� 
	mTileView = Cast<UTileView>(GetWidgetFromName(TEXT("TileView")));

	UItemDataBase* IHPPotion = NewObject<UItemDataBase>();

	IHPPotion->SetIconPath("Texture2D'/Game/Viking_RPG_UI_5_0/Buttons/Standart_buttons/Flat_Icon_18_a.Flat_Icon_18_a'");
	IHPPotion->SetItemName("HPPOTION");
	IHPPotion->SetItemCount(0);

	mTileView->AddItem(IHPPotion);


	UItemDataBase* IMPPotion = NewObject<UItemDataBase>();

	IMPPotion->SetIconPath("Texture2D'/Game/Viking_RPG_UI_5_0/Buttons/Standart_buttons/Flat_Icon_19_a.Flat_Icon_19_a'");
	IMPPotion->SetItemName("MPPOTION");
	IMPPotion->SetItemCount(0);

	mTileView->AddItem(IMPPotion);

	UItemDataBase* IBossKey = NewObject<UItemDataBase>();

	IBossKey->SetIconPath("Texture2D'/Game/Viking_RPG_UI_5_0/Buttons/Standart_buttons/Flat_Icon_28_a.Flat_Icon_28_a'");
	IBossKey->SetItemName("BossKey");
	IBossKey->SetItemCount(0);

	mTileView->AddItem(IBossKey);


	UItemDataBase* IGold = NewObject<UItemDataBase>();

	IGold->SetIconPath("Texture2D'/Game/Viking_RPG_UI_5_0/Buttons/Standart_buttons/Flat_Icon_45_a.Flat_Icon_45_a'");
	IGold->SetItemName("Gold");
	IGold->SetItemCount(0);

	mTileView->AddItem(IGold);





}

void UInventoryBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{

	Super::NativeTick(_geo, _DeltaTime);


}
