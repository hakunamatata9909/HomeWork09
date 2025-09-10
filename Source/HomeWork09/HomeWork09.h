// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class HWLibaray
{
public:
	static void MyPrintString(const AActor* InWorldContextActor, const FString& InString, float TimeToDisplay = 1.f,FColor InColor = FColor::Cyan)
	{
		if (IsValid(GEngine)&&IsValid(InWorldContextActor))
		{
			if (InWorldContextActor->GetNetMode()==NM_Client || InWorldContextActor->GetNetMode()==NM_ListenServer)
			{
				GEngine->AddOnScreenDebugMessage(-1,TimeToDisplay,InColor,InString);
			}
			else
			{
				UE_LOG(LogTemp,Log,TEXT("%s"),*InString);
			}
		}
	}

	static FString GetNetModeString(const AActor* InWorldContextActor)
	{
		FString NetModeString = TEXT("None");

		if (IsValid(InWorldContextActor))
		{
			ENetMode NetMode = InWorldContextActor->GetNetMode();
			if (NetMode==NM_Client)
			{
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = TEXT("Standalone");
				}
				else
				{
					NetModeString = TEXT("Server");
				}
			}
		}

		return NetModeString;
	}
	
	static FString GetRoleString(const AActor* InActor)
	{
		FString RoleString = TEXT("None");
		
		if(IsValid(InActor))
		{
			FString RocalRole = StaticEnum<ENetRole>()->GetNameStringByValue(InActor->GetLocalRole());
			FString RemoteRole = UEnum::GetValueAsString(TEXT("Engine.ENetRole"),InActor->GetRemoteRole());

			RoleString = FString::Printf(TEXT("Rocal : %s / Remote : %s"),*RocalRole,*RemoteRole);
		}
		return RoleString;
	}
};