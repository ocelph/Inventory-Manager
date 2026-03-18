// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleJumpPowerUpItem.h"

#include "T2_InventorySystemCharacter.h"

UDoubleJumpPowerUpItem::UDoubleJumpPowerUpItem()
{
	ItemName = "DoubleJump";
	ItemDescription = "A mysterious rune. Said to make you jump higher";
	DoubleJumpDuration = 10.f;
}

void UDoubleJumpPowerUpItem::UseItem(AT2_InventorySystemCharacter* Character)
{
	Super::UseItem(Character);
	
	if (Character)
	{
		AffectedCharacter = Character;
		AffectedCharacter->JumpMaxCount = 2;
		
		Character->GetWorld()->GetTimerManager().SetTimer(DoubleJumpPowerUpTimer, this, &UDoubleJumpPowerUpItem::OnDoubleJumpPowerUpEnd, DoubleJumpDuration, false);
	}
	
}

void UDoubleJumpPowerUpItem::OnDoubleJumpPowerUpEnd()
{
	if (AffectedCharacter)
	{
		AffectedCharacter->JumpMaxCount = 1;
		AffectedCharacter = nullptr;
		
	}
}
