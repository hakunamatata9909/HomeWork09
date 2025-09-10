// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState()
	:PlayerString(TEXT("None")),
	CurrentGuessCount(0),
	MaxGuessCount(10)
{
	bReplicates = true;
}

FString AMyPlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerString + TEXT("(") + FString::FromInt(CurrentGuessCount) + TEXT("/") + FString::FromInt(MaxGuessCount) + TEXT(")");
	return PlayerInfoString;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerString);
	DOREPLIFETIME(ThisClass, CurrentGuessCount);
	DOREPLIFETIME(ThisClass, MaxGuessCount); 
}

