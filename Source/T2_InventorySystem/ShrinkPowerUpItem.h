// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "ShrinkPowerUpItem.generated.h"

/**
*   Create a shrink powerup that allows a player to shrink to 50% size when the powerup 
*   is activated. You must make sure that the powerup effect cannot be stacked multiple 
*   times on top of each other. Make sure you give the ItemName the value “Shrink”, as 
*   other names will crash the game.
 */
UCLASS()
class T2_INVENTORYSYSTEM_API UShrinkPowerUpItem : public UItemObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShrinkPowerUpPercentage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShrinkPowerUpDuration;

	FTimerHandle ShrinkTimer;
	
	UPROPERTY(EditAnywhere)
		AT2_InventorySystemCharacter* AffectedCharacter;
	
	
public:
	UShrinkPowerUpItem();
	virtual void UseItem(AT2_InventorySystemCharacter* Character) override;
	
	UFUNCTION()
		void OnShrinkPowerUpEnd();
};
