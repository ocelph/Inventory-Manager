// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrinkPowerUpItem.h"
#include "T2_InventorySystemCharacter.h"
#include "Components/CapsuleComponent.h"

UShrinkPowerUpItem::UShrinkPowerUpItem()
{
	ItemName = "Shrink";
	ItemDescription = "A mysterious rune. Makes you shrink for 10 seconds";
	ShrinkPowerUpPercentage = 0.5f;
	ShrinkPowerUpDuration = 10.f;
}

void UShrinkPowerUpItem::UseItem(AT2_InventorySystemCharacter* Character)
{
	Super::UseItem(Character);
	
	if (Character)
	{
		if (!(Character->shrinkPowerUpActivate))
		{
			AffectedCharacter = Character;
			AffectedCharacter->shrinkPowerUpActivate = true;
			AffectedCharacter->GetCapsuleComponent()->SetRelativeScale3D(FVector(ShrinkPowerUpPercentage, ShrinkPowerUpPercentage, ShrinkPowerUpPercentage));
			Character->GetWorld()->GetTimerManager().SetTimer(ShrinkTimer, this, &UShrinkPowerUpItem::OnShrinkPowerUpEnd, ShrinkPowerUpDuration, false);
			
		}
		
	}
}

void UShrinkPowerUpItem::OnShrinkPowerUpEnd()
{
	if (AffectedCharacter->shrinkPowerUpActivate)
	{
		if(AffectedCharacter) {
			
			AffectedCharacter->GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
			AffectedCharacter->shrinkPowerUpActivate = false;
			AffectedCharacter = nullptr;
		}
	}
}
