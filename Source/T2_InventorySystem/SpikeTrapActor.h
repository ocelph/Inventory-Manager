// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "T2_InventorySystemCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeTrapActor.generated.h"

UCLASS()
class T2_INVENTORYSYSTEM_API ASpikeTrapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpikeTrapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* TrapMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* DamageVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamagePerSecond;
	
	FTimerHandle DamageTimer;
	
	UPROPERTY()
		AT2_InventorySystemCharacter* CollidingPlayer;
	
	UFUNCTION()
		void OnDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnDamageOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UFUNCTION()
		void DamageTime();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
