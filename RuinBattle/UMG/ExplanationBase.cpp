// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplanationBase.h"
#include "CharacterInfoHUDBase.h"
#include "CharacterHUDBase.h"

void UExplanationBase::NativeConstruct()
{
	mExplanBtn = Cast<UButton>(GetWidgetFromName(TEXT("ExplanBtn")));
	mInfoBtn = Cast<UButton>(GetWidgetFromName(TEXT("PlayerInfoBtn")));
	mCancelBtn = Cast<UButton>(GetWidgetFromName(TEXT("CancelBtn")));

	mExplanBtn->OnClicked.AddDynamic(this, &UExplanationBase::OnExplanBtn);
	mInfoBtn->OnClicked.AddDynamic(this, &UExplanationBase::OnInfoBtn);
	mCancelBtn->OnClicked.AddDynamic(this, &UExplanationBase::OnCancelBtn);

	SetVisibility(ESlateVisibility::Hidden);

}

void UExplanationBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

}

void UExplanationBase::ShowExplanation()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FInputModeGameAndUI all;
	PlayerController->SetInputMode(all);
	PlayerController->bShowMouseCursor = true;

	SetVisibility(ESlateVisibility::Visible);

}


void UExplanationBase::OnInfoBtn()
{
	
}

void UExplanationBase::OnExplanBtn()
{

}

void UExplanationBase::OnCancelBtn()
{
	PrintViewport(1.f, FColor::Red, TEXT("CancleBtn"));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FInputModeGameOnly GameOnly;
	PlayerController->SetInputMode(GameOnly);
	PlayerController->bShowMouseCursor = false;


	SetVisibility(ESlateVisibility::Hidden);
}
