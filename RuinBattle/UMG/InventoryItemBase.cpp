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


//�߰��� �����͸� �ʱ�ȭ�����ִ� �Լ� ����
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

		// �����Ϳ� ����ִ� ������ �̸��� ItemName �� ����� �� �ؽ�Ʈ��� ������ ����
		mItemNameTxt->SetText(FText::FromString(ItemName));

		//������ ���ڿ��� ��ȯ���Ѽ� �־���
		mCountTxt->SetText(FText::FromString(FString::Printf(TEXT("%d"), Count)));
	}

}
