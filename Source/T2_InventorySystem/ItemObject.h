// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

// forward declaration
class AT2_InventorySystemCharacter;

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
	
		// Marking a function as virtual in a base class, tells C++ this function can be overridden in a derived class
		// We will override the function each time depending on what it does
		virtual void UseItem(AT2_InventorySystemCharacter* Character);
	
};


