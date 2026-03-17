// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "T2_InventorySystemCharacter.h"


// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Every actor needs a RootComponent. It defines the actor's transform (position, rotation, scale)
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	
	// This creates the component that will display the 3D model. But this mesh isn't attached to anything yet
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	
	// Note: CreateDefaultSubobject should only be called in the constructor.
}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OnOverlap);
	
	if (!Item) // If Item pointer does not exist yet.
	{
		Item = NewObject<UItemObject>();
	}

}

void APickUpItem::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap function triggered"));
	// this: refers to the actor that owns the overlap function (PickUpItem)
	// make sure the pickup item isn’t detecting itself
	if (OtherActor && OtherActor != this)
	{
		AT2_InventorySystemCharacter* Player = Cast<AT2_InventorySystemCharacter>(OtherActor);
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player detected"));
			if (Player->AddItem(Item))
			{
				UE_LOG(LogTemp, Warning, TEXT("Item added successfully"));
				Destroy();
				UE_LOG(LogTemp, Warning, TEXT("Item destroyed successfully"));
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("Item not added!!"));
			}
		}
	}
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

