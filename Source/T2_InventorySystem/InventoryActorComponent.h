// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemObject.h"
#include "T2_InventorySystemCharacter.h"
#include "InventoryActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class T2_INVENTORYSYSTEM_API UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	
	int32 InventorySize;
	
	UPROPERTY()
	TArray<UItemObject*> InventoryItems;

public:	
	
	TArray<UItemObject*> GetAllItems();
	UItemObject* GetItemAtIndex(int32 Index);
	
	// return bool because we want to know if we were able to use/add/delete item successfully
	bool UseItemAtIndex(int32 Index, AT2_InventorySystemCharacter* Character);
	bool DeleteItemAtIndex(int32 Index);
	bool AddItem(UItemObject * NewItem);
	void CreateDefaultItems();
	
		
};
