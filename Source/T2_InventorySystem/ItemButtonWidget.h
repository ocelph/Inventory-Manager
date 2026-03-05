// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemButtonWidget.generated.h"

// An event that can be declared
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUItemButtonOnClicked, class UItemButtonWidget*, Button);

/**
 * 
 */
UCLASS()
class T2_INVENTORYSYSTEM_API UItemButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FUItemButtonOnClicked OnClickedDelegate;
	void UpdateItemIcon(UTexture2D* NewIcon);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* MainButton;

	UFUNCTION()
	void OnButtonClicked();
};
