// Copyright Epic Games, Inc. All Rights Reserved.

#include "T2_InventorySystemCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "T2_InventorySystem.h"
#include "InventoryActorComponent.h"

AT2_InventorySystemCharacter::AT2_InventorySystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	InventoryComponent = CreateDefaultSubobject<UInventoryActorComponent>(TEXT("Inventory Component"));
	bIsInventoryOpen = false;
}

void AT2_InventorySystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Different types of event triggers (ETriggerEvent):
			// Triggered is activated every single tick if the button is pressed.
			// Completed is activated when the button is released.
			// Started is activated the tick that a button is pressed.

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AT2_InventorySystemCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AT2_InventorySystemCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AT2_InventorySystemCharacter::Look);
		
		// Inventory (Open/Close)
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AT2_InventorySystemCharacter::ToggleInventory);
	}
	else
	{
		UE_LOG(LogT2_InventorySystem, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AT2_InventorySystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (InventoryWidgetClass)
		{
			InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryWidgetClass);
			InventoryWidget->Owner = this; 
		}
		
	}
}

void AT2_InventorySystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AT2_InventorySystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AT2_InventorySystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AT2_InventorySystemCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AT2_InventorySystemCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AT2_InventorySystemCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AT2_InventorySystemCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}


bool AT2_InventorySystemCharacter::AddItem(UItemObject* NewItem)
{
	return InventoryComponent->AddItem(NewItem);
}

UItemObject* AT2_InventorySystemCharacter::GetItemAtIndex(int32 Index)
{
	return InventoryComponent->GetItemAtIndex(Index);
}

void AT2_InventorySystemCharacter::DeleteItemAtIndex(int32 Index)
{
	InventoryComponent->DeleteItemAtIndex(Index);
	InventoryWidget->RefreshInventory(InventoryComponent->GetAllItems());
	
}

void AT2_InventorySystemCharacter::ToggleInventory()
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!PlayerController)
		return;
	
	if (bIsInventoryOpen)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		InventoryWidget->RemoveFromParent();
		PlayerController->bShowMouseCursor = false;
	} else
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->RefreshInventory(InventoryComponent->GetAllItems());
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = true;
	}
	bIsInventoryOpen = !bIsInventoryOpen;
}

void AT2_InventorySystemCharacter::UseItem(int32 Index)
{
	InventoryComponent->UseItemAtIndex(Index, this);
	InventoryWidget->RefreshInventory(InventoryComponent->GetAllItems());
}
