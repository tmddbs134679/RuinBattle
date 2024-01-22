// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "../RBGameInstance.h"
#include "../RuinBattleGameModeBase.h"
#include "../UMG/CharacterHUDBase.h"
#include "../UMG/InventoryBase.h"


UWorld* UInventory::mWorld = nullptr;

UInventory::UInventory()
	: mPrevSeconds(0)
{
	int a = 0;
}

UInventory::~UInventory()
{
}

bool UInventory::IsInventoryOpen()
{
	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(mWorld));

	if (GameMode == nullptr)
		return false;

	UCharacterHUDBase* CharacterHUD = GameMode->GetCharacterHUD();
	UInventoryBase* InventoryWidget = CharacterHUD->GetInventoryWidget();

	return InventoryWidget->IsVisible();
}

void UInventory::SetItemTable(UDataTable* Table)
{
	mItemTable = Table;

	FString str;
	TArray<FItemDataInfo*> ItemInfo;
	//GetAllRows���̺� ����� ������
	mItemTable->GetAllRows<FItemDataInfo>(str, ItemInfo);


	//Data Table Row ����
	TArray<FName> RowName;
	RowName = mItemTable->GetRowNames();

	for (int i = 0; i < RowName.Num(); ++i)
	{
		mRownameFromID.Add(ItemInfo[i]->ID, RowName[i]);
	}

}

//Item�� ���� �� DataTable�� ID KEY������ �����ؼ� Inventory�� �ְ� ����
const FItemDataInfo* UInventory::GetItemInfo(EITEM_ID ItemID)
{
	FName RowName = mRownameFromID.FindRef(ItemID);

	// ������ ���̺��� �˻��� �Ѵ�.
	FItemDataInfo* ItemInfo = mItemTable->FindRow<FItemDataInfo>(RowName, nullptr);

	return ItemInfo;

}



UInventory* UInventory::GetInst(UWorld* World)
{
	mWorld = World;

	URBGameInstance* GameInstance = Cast<URBGameInstance>(UGameplayStatics::GetGameInstance(World));

	if (GameInstance->mInventory == nullptr)
	{
		GameInstance->mInventory = NewObject<UInventory>();
		GameInstance->mInventory->AddToRoot();
	}

	return GameInstance->mInventory;
}


//
const FItemDataInfo* UInventory::FindItemTable(const FName& Name)
{
	return mItemTable->FindRow<FItemDataInfo>(Name, TEXT(""));
}

UInventory* UInventory::GetInst(UGameInstance* GameInst)
{
	URBGameInstance* GameInstance = Cast<URBGameInstance>(GameInst);

	// �κ��丮�� ó������ ��û�� ����
	if (GameInstance->mInventory == nullptr)
	{
		GameInstance->mInventory = NewObject<UInventory>();
		GameInstance->mInventory->AddToRoot();
	}

	return GameInstance->mInventory;
}

void UInventory::ShowInventory(bool On)
{
	int32 CurrentSeconds = 0;
	float CurrrentPartial = 0.f;

	//GetAccurateRealTime�� ��Ȯ�ϰ� �ð� üũ
	UGameplayStatics::GetAccurateRealTime(CurrentSeconds, CurrrentPartial);

	if (CurrentSeconds - mPrevSeconds < 1)
		return;

	mPrevSeconds = CurrentSeconds;



	ARuinBattleGameModeBase* GameMode = Cast<ARuinBattleGameModeBase>(UGameplayStatics::GetGameMode(mWorld));

	//main level �ƴҰ�� ����ó��
	if (GameMode == nullptr)
		return;


	UCharacterHUDBase* MainHUD = GameMode->GetCharacterHUD();
	UInventoryBase* InventoryWidget = MainHUD->GetInventoryWidget();



	if (On)
	{

		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		
		APlayerController* Controller = mWorld->GetFirstPlayerController();

		FInputModeGameAndUI all;
		Controller->SetInputMode(all);
		Controller->bShowMouseCursor = true;
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);

		APlayerController* Controller = mWorld->GetFirstPlayerController();

		FInputModeGameOnly Game;
		Controller->SetInputMode(Game);
		Controller->bShowMouseCursor = false;
	}
}



