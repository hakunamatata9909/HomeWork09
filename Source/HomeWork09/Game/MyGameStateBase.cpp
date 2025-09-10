// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "HomeWork09/PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMyGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			AMyPlayerController* MPC = Cast<AMyPlayerController>(PC);
			if (IsValid(MPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				MPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
