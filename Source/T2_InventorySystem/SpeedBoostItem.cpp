// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoostItem.h"
#include "T2_InventorySystemCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USpeedBoostItem::USpeedBoostItem()
{
	ItemName = "Speed";
	ItemDescription = "A mysterious rune. Said to make you faster";
	SpeedBoostAmount = 100.f;
	SpeedBoostDuration = 1.f;
}

void USpeedBoostItem::UseItem(AT2_InventorySystemCharacter* Character)
{
	Super::UseItem(Character);
	
	if (Character)
	{
		AffectedCharacter = Character;
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed += SpeedBoostAmount;
		
		// Character->GetWorld(): Gets a pointer to the UWorld object that the character exists in
		// GetWorld()->GetTimerManager(): every UWorld has a timer manager (FTimerManager) that handles timed events
		/* SetTimer: 
		 *  BoostTimer: An FTimerHandle used to reference this timer.It can be used to pause, clear, or check the timer later
		 *  this: the SpeedBoostItem itself
		 *  &USpeedBoostItem::OnSpeedBoostEnd: function to call when the timer ends (the function we call must match "void FunctionName() signature")
		 *  SpeedBoostDuration: How long to wait (in seconds) before calling the function
		 *  false/ true: Whether the timer loops. false = run once, true = repeat forever
		*/
		
		Character->GetWorld()->GetTimerManager().SetTimer(BoostTimer, this, &USpeedBoostItem::OnSpeedBoostEnd, SpeedBoostDuration, false);
	}
}

void USpeedBoostItem::OnSpeedBoostEnd()
{
	if(AffectedCharacter) {
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed -= SpeedBoostAmount;
		AffectedCharacter = nullptr;
	}

}
