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
	
	UE_LOG(LogTemp, Warning, TEXT("Entered ShrinkPowerUpItem"));
	UE_LOG(LogTemp, Warning, TEXT("shrinkPowerUpActivate = %s"), Character->shrinkPowerUpActivate ? TEXT("true") : TEXT("false"));
	
	if (Character)
	{
		if (!(Character->shrinkPowerUpActivate))
		{
			
			
			AffectedCharacter = Character;
			AffectedCharacter->shrinkPowerUpActivate = true;
			
			
			AffectedCharacter->GetMesh()->SetWorldScale3D(FVector(ShrinkPowerUpPercentage));
			// UCapsuleComponent* CollisonCapsule = AffectedCharacter->GetCapsuleComponent();
			//
			// // Half Height = distance from the center of the capsule to the top (or bottom)
			// float InitialHalfHeight = CollisonCapsule->GetUnscaledCapsuleHalfHeight();
			// float InitialRadius = CollisonCapsule->GetUnscaledCapsuleRadius();
			//
			// UE_LOG(LogTemp, Warning, TEXT("InitialHalfHeight: %f"),InitialHalfHeight );
			// UE_LOG(LogTemp, Warning, TEXT("InitialRadius: %f"),InitialRadius );
			//
			// CollisonCapsule->SetCapsuleHalfHeight(InitialHalfHeight * ShrinkPowerUpPercentage);
			// CollisonCapsule->SetCapsuleRadius(InitialRadius * ShrinkPowerUpPercentage);
			
			// UE_LOG(LogTemp, Warning, TEXT("CurrentHalfHeight: %f"), CollisonCapsule->GetUnscaledCapsuleHalfHeight() );
			// UE_LOG(LogTemp, Warning, TEXT("CurrentlRadius: %f"),CollisonCapsule->GetUnscaledCapsuleRadius() );
			
			Character->GetWorld()->GetTimerManager().SetTimer(ShrinkTimer, this, &UShrinkPowerUpItem::OnShrinkPowerUpEnd, ShrinkPowerUpDuration, false);
		
			
		}
		
	}
}

void UShrinkPowerUpItem::OnShrinkPowerUpEnd()
{
	if (AffectedCharacter->shrinkPowerUpActivate)
	{
		if(AffectedCharacter) {
			
			AffectedCharacter->GetMesh()->SetWorldScale3D(FVector(1));
			
			// float CurrentHalfHeight = AffectedCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
			// float CurrentRadius = AffectedCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
			//
			// AffectedCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(CurrentHalfHeight * (1/ShrinkPowerUpPercentage));
			// AffectedCharacter->GetCapsuleComponent()->SetCapsuleRadius(CurrentRadius * (1/ShrinkPowerUpPercentage));
			
			AffectedCharacter->shrinkPowerUpActivate = false;
			AffectedCharacter = nullptr;
		}
	}
}
