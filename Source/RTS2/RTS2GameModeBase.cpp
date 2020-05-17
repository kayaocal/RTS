// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "RTS2GameModeBase.h"
#include "RTS2/Public/RTSPlayerCameraSpectatorPawn.h"
#include "RTS2/Public/RTSHud.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Game/RTSManager.h"

ARTS2GameModeBase::ARTS2GameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
	HUDClass = ARTSHud::StaticClass();
}

void ARTS2GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	if(GetWorld())
	{
		if(GetWorld()->WorldType == EWorldType::PIE  || GetWorld()->WorldType == EWorldType::Game )
		{
			if(RTSManager::GetInstance().Existance == EGameExistance::None)
			{
				RTSManager::GetInstance().SetGameExistance(EGameExistance::QuickGame);
			}
		}
	}
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ARTS2GameModeBase::StartPlay()
{

	
	Super::StartPlay();
}
