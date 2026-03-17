// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemObject.h"
#include "SpeedBoostItem.generated.h"

/**
 * 
 */
UCLASS()
class T2_INVENTORYSYSTEM_API USpeedBoostItem : public UItemObject
{
	GENERATED_BODY()
	
	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float SpeedBoostAmount;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float SpeedBoostDuration;
	
		FTimerHandle BoostTimer;
	
		UPROPERTY(EditAnywhere)
			AT2_InventorySystemCharacter* AffectedCharacter;
	
	public:
		USpeedBoostItem();
	
		virtual void UseItem(AT2_InventorySystemCharacter* Character) override;
		
		UFUNCTION()
			void OnSpeedBoostEnd();
	
};

