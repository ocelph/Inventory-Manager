// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"

UCLASS()
class T2_INVENTORYSYSTEM_API APickUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	UStaticMeshComponent* MeshComponent;
	
	// will represent the item in the game world that player can collect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	UItemObject* Item;

	// UFUNCTION will allow the function to be bound to an overlap event
	// E.g: MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlap);
	/*        OverlapComp: The actor component on you (the player) that detected the collision
	 *     OtherActor: The actor that touched the PickUpItem
	 *      OtherComp: The specific component that touched you
	 * OtherBodyIndex: Used internally for physics when an actor has multiple bodies (usually ignored)
	 *     bFromSweep: Whether the overlap came from a sweep
	 *    SweepResult: Detailed collision info (Impact point, Damage, hit location, etc)
	*/ 
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
