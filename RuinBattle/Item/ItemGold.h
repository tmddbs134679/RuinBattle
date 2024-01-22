// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemActor.h"
#include "ItemGold.generated.h"

/**
 * 
 */
UCLASS()
class RUINBATTLE_API AItemGold : public AItemActor
{
	GENERATED_BODY()
	
public:
	AItemGold();



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMesh* mGoldBar;



};
