// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerLobbyGameMode.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Public/RTSPlayerCameraSpectatorPawn.h"
#include "RTS2/Public/RTSPlayerController.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();


}

void AMultiplayerLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	LOG("Player Logged In");
	Super::PostLogin(NewPlayer);
	if(ConnActor == nullptr)
	{
		ConnActor = GetWorld()->SpawnActor<AMultiplayerSetupConnActor>(AMultiplayerSetupConnActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	}
	FRPCData data;
	
	ConnActor->SayHiRPC(data);
		
}

void AMultiplayerLobbyGameMode::PreLogin(const FString& Options, const FString& Address,
	const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	LOG("Player PreLogin");
}

void AMultiplayerLobbyGameMode::Logout(AController* Exiting)
{
	LOG("Player Logged Out");
	Super::Logout(Exiting);
	
}

void AMultiplayerLobbyGameMode::StartPlay()
{
	Super::StartPlay();
	ConnActor = GetWorld()->SpawnActor<AMultiplayerSetupConnActor>(AMultiplayerSetupConnActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

}

