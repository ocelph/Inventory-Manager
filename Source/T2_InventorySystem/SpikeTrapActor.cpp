// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrapActor.h"

// Sets default values
ASpikeTrapActor::ASpikeTrapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	DamagePerSecond = 10;
	CollidingPlayer = nullptr;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Mesh"));
	TrapMesh->SetupAttachment(RootComponent);
	
	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Volume"));
	DamageVolume->SetupAttachment(TrapMesh);

}

// Called when the game starts or when spawned
void ASpikeTrapActor::BeginPlay()
{
	Super::BeginPlay();
	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrapActor::OnDamageOverlapBegin);
	DamageVolume->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrapActor::OnDamageOverlapEnd);
}

void ASpikeTrapActor::OnDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// checks if other actor is acually another actor and not spike itself
	if (OtherActor && OtherActor != this)
	{
		AT2_InventorySystemCharacter* TempCharacter = Cast<AT2_InventorySystemCharacter>(OtherActor);
		if (TempCharacter)
		{
			CollidingPlayer = TempCharacter;
			
			/* SetTimer: 
			 *  DamageTimer: An FTimerHandle used to reference this timer.It can be used to pause, clear, or check the timer later
			 *  this: the SpeedBoostItem itself
			 *  &ASpikeTrapActor::DamageTimer: function to call when the timer ends (the function we call must match "void FunctionName() signature")
			 *  1 sec : How long to wait (in seconds) before calling the function
			 *  false/ true: Whether the timer and subsequemt function call loops. false = run once, true = repeat forever
			*/
			GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &ASpikeTrapActor::DamageTime,
				1,true);
		}
	}
	
	
}

// This function is called when something stops overlapping with the DamageVolume
void ASpikeTrapActor::OnDamageOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// we clear the timer and set CollidingPlayer back to nullptr
	if(OtherActor == CollidingPlayer)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimer);
		CollidingPlayer = nullptr;
	}
}

// This function is called every time the timer goes off
void ASpikeTrapActor::DamageTime()
{
	if(CollidingPlayer){
		CollidingPlayer->DamagePlayer(DamagePerSecond);
	}

}

// Called every frame
void ASpikeTrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

