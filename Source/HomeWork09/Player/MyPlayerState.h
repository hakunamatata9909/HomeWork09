// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK09_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();

	FString GetPlayerInfoString();
	UPROPERTY(Replicated)
	FString PlayerString;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;
	UPROPERTY(Replicated)
	int32 MaxGuessCount;
};
