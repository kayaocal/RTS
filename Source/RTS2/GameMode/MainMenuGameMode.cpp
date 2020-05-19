// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"


#include "RTSPlayerCameraSpectatorPawn.h"
#include "RTS2/Game/MainMenuPlayerController.h"
#include "RTS2/Game/RTSManager.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
}

void AMainMenuGameMode::StartPlay()
{
	Super::StartPlay();
}

void AMainMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	if(RTSManager::GetInstance().Existance == EGameExistance::None)
	{
		RTSManager::GetInstance().SetGameExistance(EGameExistance::Game);
	}

	Super::InitGame(MapName, Options, ErrorMessage);
	
}
