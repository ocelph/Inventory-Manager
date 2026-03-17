// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InventoryWidget.h"
#include "ItemObject.h"
#include "T2_InventorySystemCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AT2_InventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

public:

	/** Constructor */
	AT2_InventorySystemCharacter();	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	
	// EditAnywhere: It means that the value can be edited from the editor, code, or blueprints.
	// BlueprintReadOnly: Blueprints can read the value but cannot modify it
	// Category = "Inventory": Instead of being in Default, it appears under Inventory > InventorySize
	// Category allows us to specify a category it will appear in editor when editing a Blueprint subclass or an instance in the Game World

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventoryActorComponent* InventoryComponent;


public:
	bool AddItem(UItemObject* NewItem);
	
	/* These functions will allow us to provide indices and either get the item in our inventory at
	that index, or delete it! */
	UItemObject* GetItemAtIndex(int32 Index);
	void DeleteItemAtIndex(int32 Index);
	
	
public:
	// These functions and variables were added for the Inventory Action we created
	
	//  store a reference of the action in the character class so that the action can be bound to a specific function
	UPROPERTY(EditAnywhere)
	UInputAction* InventoryAction;
	
	//  variable to track the state of our inventory
	bool bIsInventoryOpen;
	
	// function that will be called when the action is triggered
	UFUNCTION()
	void ToggleInventory();
	
};

