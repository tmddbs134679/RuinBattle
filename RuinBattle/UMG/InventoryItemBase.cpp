// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"

#include "ItemDataBase.h"

void UInventoryItemBase::NativeConstruct()
{
	Super::NativeConstruct();


	mIconImg = Cast<UImage>(GetWidgetFromName(FName("Icon")));
	mItemNameTxt = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ItemName"))));
	mCountTxt = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Count"))));
}

void UInventoryItemBase::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
	
}


//추가된 데이터를 초기화시켜주는 함수 생성
void UInventoryItemBase::InitFromData(UObject* _Data)
{
	UItemDataBase* IData = Cast<UItemDataBase>(_Data);

	if (IsValid(IData))
	{
		const FString& IconPath = IData->GetIconPath();
		const FString& ItemName = IData->GetItemName();

		IData->SetItemCount(1);
		int Count = IData->GetItemCount();


		UTexture2D* Txt = LoadObject<UTexture2D>(nullptr, *IconPath);
		if (IsValid(Txt))
		{
			mIconImg->SetBrushFromTexture(Txt);
		}

		// 데이터에 들어있던 아이템 이름을 ItemName 을 출력해 줄 텍스트블록 위젯에 전달
		mItemNameTxt->SetText(FText::FromString(ItemName));

		//정수형 문자열로 전환시켜서 넣어줌
		mCountTxt->SetText(FText::FromString(FString::Printf(TEXT("%d"), Count)));
	}

}
