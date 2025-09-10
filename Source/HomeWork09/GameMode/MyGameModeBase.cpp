// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "HomeWork09/PlayerController/MyPlayerController.h"
#include "HomeWork09/Game/MyGameStateBase.h"
#include "HomeWork09/Player/MyPlayerState.h"
#include "EngineUtils.h"

void AMyGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AMyPlayerController* MyController = Cast<AMyPlayerController>(NewPlayer);

	if (IsValid(MyController))
	{
		PlayerControllers.Add(MyController);
		MyController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
		AMyPlayerState* MyPlayerState = MyController->GetPlayerState<AMyPlayerState>();
		if (IsValid(MyPlayerState))
		{
			MyPlayerState->PlayerString =TEXT("Player ")+FString::FromInt(PlayerControllers.Num());
		}

		AMyGameStateBase* MyGameStateBase = GetGameState<AMyGameStateBase>();
		if (IsValid(MyGameStateBase))
		{
			MyGameStateBase->MulticastRPCBroadcastLoginMessage(MyPlayerState->PlayerString);
		}
	}
}

FString AMyGameModeBase::GeneratSecretNumber()
{
	TArray<int32>Numbers;

	for (int32 i = 1; i<=9;i++)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 num){return num>0;});
	
	FString Result;
	for (int32 i=0;i<3;++i)
	{
		int32 Index = FMath::RandRange(0,Numbers.Num()-1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}
	
	return Result;
}

bool AMyGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay=false;

	do
	{
		if (InNumberString.Len()!=3)
		{
			break;
		}

		bool bIsUnique = true;

		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (!FChar::IsDigit(C) || C=='0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (!bIsUnique)
		{
			break;
		}

		bCanPlay = true;
	}while (false);

	return bCanPlay;
}

FString AMyGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount=0,BallCount=0;

	for (int32 i=0; i<3;++i)
	{
		if (InSecretNumberString[i]==InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount==0&&BallCount==0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void AMyGameModeBase::IncreaseGuessCount(AMyPlayerController* InChattingPlayerController)
{
	AMyPlayerState* MyPlayerState = InChattingPlayerController->GetPlayerState<AMyPlayerState>();
	if (IsValid(MyPlayerState))
	{
		MyPlayerState->CurrentGuessCount++;
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString=GeneratSecretNumber();
}

void AMyGameModeBase::PrintChatMessageString(AMyPlayerController* InChattingPlayerController,
	const FString& InChatMessageString)
{
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		IncreaseGuessCount(InChattingPlayerController);
		for (TActorIterator<AMyPlayerController> It(GetWorld()); It; ++It)
		{
			AMyPlayerController* CXPlayerController = *It;
			if (IsValid(CXPlayerController) == true)
			{
				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				CXPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
	else
	{
		for (TActorIterator<AMyPlayerController> It(GetWorld()); It; ++It)
		{
			AMyPlayerController* CXPlayerController = *It;
			if (IsValid(CXPlayerController) == true)
			{
				CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

void AMyGameModeBase::ResetGame()
{
	SecretNumberString=GeneratSecretNumber();

	for (const auto& MyPlayerController : PlayerControllers)
	{
		AMyPlayerState* MyPlayerState = MyPlayerController->GetPlayerState<AMyPlayerState>();
		if (IsValid(MyPlayerState))
		{
			MyPlayerState->CurrentGuessCount = 0;
		}
	}
}

void AMyGameModeBase::JudgeGame(AMyPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3==InStrikeCount)
	{
		AMyPlayerState* MyPlayerState = InChattingPlayerController->GetPlayerState<AMyPlayerState>();
		for (const auto& MyPlayerController : PlayerControllers)
		{
			if (IsValid(MyPlayerState))
			{
				FString CombinedMesaageString = MyPlayerState -> PlayerString+TEXT(" has won the game");
				MyPlayerController->NotificationText = FText::FromString(CombinedMesaageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& CXPlayerController : PlayerControllers)
		{
			AMyPlayerState* CXPS = CXPlayerController->GetPlayerState<AMyPlayerState>();
			if (IsValid(CXPS) == true)
			{
				if (CXPS->CurrentGuessCount < CXPS->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}
		if (bIsDraw)
		{
			for (const auto& MyPlayerController : PlayerControllers)
			{
				MyPlayerController->NotificationText=FText::FromString(TEXT("DRAW"));
				ResetGame();
			}
		}
	}
	
}

