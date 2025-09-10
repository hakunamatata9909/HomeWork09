// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "HomeWork09/HomeWork09.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = HWLibaray::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("MyPawn::BeginPlay() %s [%s]"), *HWLibaray::GetNetModeString(this), *NetRoleString);
	HWLibaray::MyPrintString(this, CombinedString, 10.f);
}

void AMyPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = HWLibaray::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("MyPawn::PossessedBy() %s [%s]"), *HWLibaray::GetNetModeString(this), *NetRoleString);
	HWLibaray::MyPrintString(this, CombinedString, 10.f);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

