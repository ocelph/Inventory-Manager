// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "DoubleJumpPowerUpItem.generated.h"

/**
 * 
 */
UCLASS()
class T2_INVENTORYSYSTEM_API UDoubleJumpPowerUpItem : public UItemObject
{
	GENERATED_BODY()
	
	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DoubleJumpDuration;
		
		FTimerHandle DoubleJumpPowerUpTimer;
		
		UPROPERTY(EditAnywhere)
		AT2_InventorySystemCharacter* AffectedCharacter;
		
	public:
		UDoubleJumpPowerUpItem();
		
		virtual void UseItem(AT2_InventorySystemCharacter* Character) override;
			
		UFUNCTION()
		void OnDoubleJumpPowerUpEnd();
		
};
