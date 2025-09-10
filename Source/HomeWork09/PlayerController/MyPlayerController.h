// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HomeWork09/ChatInput/MyUserWidget.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class HOMEWORK09_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	AMyPlayerController();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;
	
	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);
	
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UMyUserWidget> WidgetClass;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UMyUserWidget> WidgetClasssInstance;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
	
	protected:
	FString ChatMessageString;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;
};
