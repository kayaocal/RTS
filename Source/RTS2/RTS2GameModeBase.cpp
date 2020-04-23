// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "RTS2GameModeBase.h"
#include "RTS2/Public/RTSPlayerCameraSpectatorPawn.h"
#include "RTS2/Public/RTSHud.h"
#include "RTS2/Public/RTSPlayerController.h"

ARTS2GameModeBase::ARTS2GameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
	HUDClass = ARTSHud::StaticClass();
}
