// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AMyPlayerController;
/**
 * 
 */
UCLASS()
class HOMEWORK09_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void OnPostLogin(AController* NewPlayer) override;	
	FString GeneratSecretNumber();
	bool IsGuessNumberString(const FString& InNumberString);
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);
	void IncreaseGuessCount(AMyPlayerController* InChattingPlayerController);
	virtual void BeginPlay() override;
	void PrintChatMessageString(AMyPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	void ResetGame();
	void JudgeGame(AMyPlayerController* InChattingPlayerController, int InStrikeCount);
protected:
	FString SecretNumberString;
	TArray<TObjectPtr<AMyPlayerController>> PlayerControllers;

};
