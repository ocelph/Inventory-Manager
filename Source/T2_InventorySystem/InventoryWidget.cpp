// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "T2_InventorySystemCharacter.h"
#include "ItemButtonWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"


void UInventoryWidget::RefreshInventory(TArray<UItemObject*> Items)
{
	for (UItemButtonWidget* Btn : ButtonList)
	{
		Btn->UpdateItemIcon(*ImageMap.Find("None"));
	}
	
	for (int i = 0; i < Items.Num(); i++)
	{
		if (i > ButtonList.Num() - 1)
		{
			return;
		}
		ButtonList[i]->UpdateItemIcon(*ImageMap.Find(Items[i]->GetName()));
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(ButtonList.Num() > 0) {
		return;
	}

	for(int32 Y = 0; Y < NumButtonHeight; Y++)
	{
		for(int32 X = 0; X < NumButtonWidth; X++)
		{
			FString WidgetName = FString::Printf(TEXT("Button_X%d_Y%x"), X, Y);

			if (BPButtonWidget)
			{
				UItemButtonWidget* Button = WidgetTree->ConstructWidget<UItemButtonWidget>(BPButtonWidget, FName(WidgetName));

				ButtonList.Add(Button);
				Button->OnClickedDelegate.AddDynamic(this, &UInventoryWidget::OnButtonWasClicked);
				InventoryGrid->AddChildToGrid(Button, Y, X);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("BPButtonWidget is null"));
			}
			
		}
	}
	
	ItemNameTextBlock->SetText(FText::FromString("No Item Selected"));
	ItemDescriptionTextBlock->SetText(FText::FromString("No Item Selected"));

	UseItemButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnUseButtonClicked);
	DeleteItemButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnDeleteButtonClicked);
}

void UInventoryWidget::OnButtonWasClicked(UItemButtonWidget* Button)
{
	SelectedItemIndex = ButtonList.Find(Button);
	
	UE_LOG(LogTemp, Warning, TEXT("Button %s, Index %d"), *Button->GetName(), SelectedItemIndex);
	
	UItemObject* SelectedItem = Owner -> GetItemAtIndex(SelectedItemIndex);
	
	if (SelectedItem)
	{
		ItemNameTextBlock-> SetText(FText:: FromString (SelectedItem->GetName()));
		ItemDescriptionTextBlock->SetText(FText::FromString(SelectedItem->GetDescription()));
	}
}

void UInventoryWidget::OnUseButtonClicked()
{
	
}

void UInventoryWidget::OnDeleteButtonClicked()
{	
	Owner-> DeleteItemAtIndex(SelectedItemIndex);
	ItemNameTextBlock-> SetText(FText::FromString("No Item Selected"));
	ItemDescriptionTextBlock-> SetText(FText:: FromString("No Item Selected"));
}