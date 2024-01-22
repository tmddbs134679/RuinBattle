// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "../Inventory/Inventory.h"
#include "../UMG/InventoryBase.h"
#include "../Player/PlayerCharacter.h"
#include "../UMG/ItemDataBase.h"
#include <Components/TileView.h>

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(mSphere);

	mMesh->SetupAttachment(mSphere);

	// Item -> 플레이어와 충돌하지 않고 획득 가능하게 세팅

	mSphere->SetCollisionProfileName(TEXT("Item"));
	mSphere->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;
	mSphere->SetGenerateOverlapEvents(true);
	mSphere->CanEverAffectNavigation();
	mSphere->SetSphereRadius(100.f);

	mMesh->SetCollisionProfileName(TEXT("NoCollision"));
	mMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mMesh->SetGenerateOverlapEvents(false);

}


// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::BeginOverlap);



}

void AItemActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintViewport(1.f, FColor::Red, TEXT("Overlap"));


	UItemDataBase* IGold = NewObject<UItemDataBase>();

	IGold->SetIconPath("Texture2D'/Game/Viking_RPG_UI_5_0/Buttons/Standart_buttons/Flat_Icon_18_a.Flat_Icon_18_a'");
	IGold->SetItemName("Gold");
	IGold->SetItemCount(0);
	

	
	Destroy();
}

void AItemActor::SetMesh(const FString& Path)
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *Path);

	if (IsValid(Mesh))
		mMesh->SetStaticMesh(Mesh);

}

