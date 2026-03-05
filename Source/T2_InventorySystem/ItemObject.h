// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS()
class T2_INVENTORYSYSTEM_API UItemObject : public UObject
{
	GENERATED_BODY()
	
	protected: 
		FString ItemName;
		FString ItemDescription;
		
	public:
		UItemObject();
		void SetName(FString Name);
		void SetDescription(FString Description);
		FString GetName();
		FString GetDescription();
	
};


