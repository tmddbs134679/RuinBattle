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


	//위젯에 만든 모든 anim 가져오기
	UWidgetBlueprintGeneratedClass* WidgetBPClass = GetWidgetTreeOwningClass();

	for (int i = 0; i < WidgetBPClass->Animations.Num(); ++i)
	{
		//만든 tmap 에 저장후 사용
		FString AnimName = WidgetBPClass->Animations[i]->GetName();
		mWidgetAim.Add(AnimName, WidgetBPClass->Animations[i]);

	}

}

void UStartHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);
}



//버튼 클릭시 레벨 전환
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
	//호버 anim 가져올 때 -> _INST
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
