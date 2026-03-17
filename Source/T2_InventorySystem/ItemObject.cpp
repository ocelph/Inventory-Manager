// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"

UItemObject::UItemObject()
{
	ItemName = FString("None");
	ItemDescription = FString("A default description");
}

void UItemObject::SetName(FString Name)
{
	ItemName = Name;
}

void UItemObject::SetDescription(FString Description)
{
	ItemDescription = Description;
}

FString UItemObject::GetName()
{
	return ItemName;
}

FString UItemObject::GetDescription()
{
	return ItemDescription;
}

void UItemObject::UseItem(AT2_InventorySystemCharacter* Character)
{
	// leave empty for now
}
