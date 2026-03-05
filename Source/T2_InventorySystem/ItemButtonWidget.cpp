// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemButtonWidget.h"
#include "Components/Button.h"

void UItemButtonWidget::UpdateItemIcon(UTexture2D* NewIcon)
{
	FButtonStyle NewStyle = MainButton->GetStyle();
	NewStyle.Normal.SetResourceObject(NewIcon);
	NewStyle.Hovered.SetResourceObject(NewIcon);
	NewStyle.Pressed.SetResourceObject(NewIcon);
	NewStyle.Disabled.SetResourceObject(NewIcon);
	MainButton->SetStyle(NewStyle);
}

void UItemButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddUniqueDynamic(this, &UItemButtonWidget::OnButtonClicked);
}

void UItemButtonWidget::OnButtonClicked()
{
	OnClickedDelegate.Broadcast(this);
}