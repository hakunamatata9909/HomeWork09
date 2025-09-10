// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"
#include "HomeWork09/GameMode/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "HomeWork09/Player/MyPlayerState.h"
#include "Net/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
		return;

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (WidgetClass)
	{
		WidgetClasssInstance = CreateWidget<UMyUserWidget>(this, WidgetClass);
		if (IsValid(WidgetClasssInstance))
		{
			WidgetClasssInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}

	}
}

void AMyPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController())
	{
		AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
		if (IsValid(MyPlayerState) == true)
		{
			FString CombinedMessageString = MyPlayerState->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void AMyPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this,InChatMessageString,true,true,FLinearColor::White,10.0f);
}

void AMyPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AMyPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(GM);
		if (IsValid(MyGameMode) == true)
		{
			MyGameMode->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, NotificationText);
}
