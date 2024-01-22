// Fill out your copyright notice in the Description page of Project Settings.


#include "StartHUDBase.h"

void UStartHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	mStartBtn = Cast<UButton>(GetWidgetFromName(TEXT("StartBtn")));
	mEndBtn = Cast<UButton>(GetWidgetFromName(TEXT("EndBtn")));


	mStartBtn->OnClicked.AddDynamic(this, &UStartHUDBase::OnStartBtnClicked);
	mStartBtn->OnHovered.AddDynamic(this, &UStartHUDBase::OnStartBtnHover);
	mStartBtn->OnUnhovered.AddDynamic(this, &UStartHUDBase::OnStartBtnUnHover);


	mEndBtn->OnClicked.AddDynamic(this, &UStartHUDBase::OnEndBtnClicked);
	mEndBtn->OnHovered.AddDynamic(this, &UStartHUDBase::OnEndBtnHover);
	mEndBtn->OnUnhovered.AddDynamic(this, &UStartHUDBase::OnEndBtnUnHover);


	//������ ���� ��� anim ��������
	UWidgetBlueprintGeneratedClass* WidgetBPClass = GetWidgetTreeOwningClass();

	for (int i = 0; i < WidgetBPClass->Animations.Num(); ++i)
	{
		//���� tmap �� ������ ���
		FString AnimName = WidgetBPClass->Animations[i]->GetName();
		mWidgetAim.Add(AnimName, WidgetBPClass->Animations[i]);

	}

}

void UStartHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}



//��ư Ŭ���� ���� ��ȯ
void UStartHUDBase::OnStartBtnClicked()
{
	//fname bool 
	if (!mNextLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(), mNextLevelName);
	}

}

void UStartHUDBase::OnStartBtnHover()
{
	//ȣ�� anim ������ �� -> _INST
	UWidgetAnimation* WidgetAnim = mWidgetAim.FindRef(TEXT("StartBtnHover_INST"));
	
	if (IsValid(WidgetAnim))
	{
		PlayAnimation(WidgetAnim);
	}

}

void UStartHUDBase::OnStartBtnUnHover()
{
	UWidgetAnimation* WidgetAnim = mWidgetAim.FindRef(TEXT("StartBtnUnHover_INST"));

	if (IsValid(WidgetAnim))
	{
		PlayAnimation(WidgetAnim);
	}
}

void UStartHUDBase::OnEndBtnClicked()
{
	FGenericPlatformMisc::RequestExit(true);
}

void UStartHUDBase::OnEndBtnHover()
{
	UWidgetAnimation* WidgetAnim = mWidgetAim.FindRef(TEXT("EndBtnHover_INST"));

	if (IsValid(WidgetAnim))
	{
		PlayAnimation(WidgetAnim);
	}
}

void UStartHUDBase::OnEndBtnUnHover()
{
	UWidgetAnimation* WidgetAnim = mWidgetAim.FindRef(TEXT("EndBtnUnHover_INST"));

	if (IsValid(WidgetAnim))
	{
		PlayAnimation(WidgetAnim);
	}
}
