// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "T2_InventorySystemCharacter.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

/**
* UCLASS Macros
	Whilst we have to put some additional properties into the UCLASS for this class, we do
	not often need to make these sorts of changes. They only occur when working with UObjects.

* BlueprintType and Blueprintable enable us to create Blueprint Subclasses of our Items.
  UObject cannot do this by default unlike Actors, so this is a required step

* EditInlineNew and DefaultToInstanced will enable us to quickly and easily set Items from the 
  Editor whenever we place a PickupItem into the world
 */

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)

class AT2_InventorySystemCharacter;

class T2_INVENTORYSYSTEM_API UItemObject : public UObject
{
	GENERATED_BODY()
	
	protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
		FString ItemDescription;
		
	public:
		UItemObject();
		void SetName(FString Name);
		void SetDescription(FString Description);
		FString GetName();
		FString GetDescription();
	
		void UseItem(AT2_InventorySystemCharacter* Character);
	
};


