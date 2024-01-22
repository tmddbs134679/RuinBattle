// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameModeBase.h"

AStartGameModeBase::AStartGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> Finder(TEXT("WidgetBlueprint'/Game/Blueprint/UMG/UI_StartHUD.UI_StartHUD_C'"));

	if (Finder.Succeeded())
	{
		mStartHUDClass = Finder.Class;
	}
}

void AStartGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	mStartHUD = Cast<UUserWidget>(CreateWidget(GetWorld(), mStartHUDClass));

	if (IsValid(mStartHUDClass))
	{
		mStartHUD->AddToViewport();
	}
}

void AStartGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
