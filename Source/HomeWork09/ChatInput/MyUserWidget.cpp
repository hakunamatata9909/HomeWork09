// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "HomeWork09/PlayerController/MyPlayerController.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	EditableTextBox_ChatInput->OnTextCommitted.AddUniqueDynamic(this,&UMyUserWidget::OnChatInputTextCommitted);
}
void UMyUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this,&UMyUserWidget::OnChatInputTextCommitted);
}

void UMyUserWidget::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* PlayerController = GetOwningPlayer();
		if (PlayerController)
		{
			AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(PlayerController);
			if (MyPlayerController)
			{
				MyPlayerController->SetChatMessageString(Text.ToString());
				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}



