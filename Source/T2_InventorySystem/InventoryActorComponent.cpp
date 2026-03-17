// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActorComponent.h"

#include "ShrinkPowerUpItem.h"

// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InventorySize = 12;

	// ...
}


// Called when the game starts
void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Generate Items at the start of the play
	CreateDefaultItems();
	
	// ...
	
}

TArray<UItemObject*> UInventoryActorComponent::GetAllItems()
{
	return InventoryItems;
}

UItemObject* UInventoryActorComponent::GetItemAtIndex(int32 Index)
{
	if(Index >= InventoryItems.Num() || Index < 0)
	{
		return nullptr;
	}
	
	return InventoryItems[Index];
}

bool UInventoryActorComponent::UseItemAtIndex(int32 Index, AT2_InventorySystemCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item"));
	if (Index >= InventoryItems.Num() || Index < 0)
	{
		return false;
	}
	UItemObject* UsedItem = InventoryItems[Index];
	UsedItem-> UseItem(Character);
	InventoryItems.RemoveAt(Index);
	
	return true;
}

bool UInventoryActorComponent::DeleteItemAtIndex(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Delete Item"));
	if (Index >= InventoryItems.Num() || Index < 0)
	{
		return false;
	}
	
	InventoryItems.RemoveAt(Index);
	return true;
}

bool UInventoryActorComponent::AddItem(UItemObject* NewItem)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Item"));
	// UE_LOG(LogTemp, Warning, TEXT("Number of items in inventory are: %d"), InventoryItems.Num());
	// check if there is still space in the inventory. if there is add and return true, else return false
	if (InventoryItems.Num() >= InventorySize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full"));
		return false;
	}
	
	// could do an if else but anyway it wont reach here if it goes into the if statement
	InventoryItems.Add(NewItem);
	
	return true;
	
}

void UInventoryActorComponent::CreateDefaultItems()
{
	// Declares a pointer variable named TempItem of type UItemObject
	UItemObject* TempItem;
	
	// Creates a new instance of UItemObject in memory.
	// NewObject is used for creating new UObject instances at runtime.
	// we have to instantiate a new object every time because these are pointers so they need to be objects of their own, if we just SetName, it would be changing the same object 
	
	TempItem = NewObject<UItemObject>();
	TempItem->SetName("Health");
	TempItem->SetDescription("A potion to recover lost health");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UShrinkPowerUpItem>();
	TempItem->SetName("Shrink");
	TempItem->SetDescription("Makes you shrink for 10 seconds");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UShrinkPowerUpItem>();
	TempItem->SetName("Shrink");
	TempItem->SetDescription("Makes you shrink for 10 seconds");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UItemObject>();
	TempItem->SetName("Freeze");
	TempItem->SetDescription("Makes you freeze for 10 seconds");
	InventoryItems.Add(TempItem);
	
	
}


