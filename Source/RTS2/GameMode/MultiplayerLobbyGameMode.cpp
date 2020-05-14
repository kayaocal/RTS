// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerLobbyGameMode.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Public/RTSPlayerCameraSpectatorPawn.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Game/MultiplayerSetupPlayerController.h"
#include "RTS2/Game/RTSManager.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	PlayerControllerClass = AMultiplayerSetupPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
	ControllerCount = 0;

}

void AMultiplayerLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	LOG("Player Logged In");
	Super::PostLogin(NewPlayer);
	array[ControllerCount] = ((AMultiplayerSetupPlayerController*)(NewPlayer));
	ControllerCount++;
	
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

void AMultiplayerLobbyGameMode::PlayerIsRead(int PlayerIndex)
{
	bUseSeamlessTravel = true;
	GetWorld()->ServerTravel("/Game/DebugLevel?listen");
}

void AMultiplayerLobbyGameMode::StartPlay()
{
	Super::StartPlay();
	RTS_GAME->GameMode = FRTSGameMode();
	RTS_GAME->GameMode.SetGamePlayType(EGamePlayType::Multiplayer);
	RTS_GAME->GameMode.SetNumberOfPlayers(2);
}

