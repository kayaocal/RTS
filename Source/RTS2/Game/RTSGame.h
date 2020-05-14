// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSGameMode.h"
#include "vector"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSNation.h"

/**
 *	Main Class of game.
 *	Game State, Players, Nations etc
 *	RTSGame class rule them all.
 */


class RTS2_API RTSGame
{

public:

	RTSGame();
	RTSGame(const FRTSGameMode& GameMode);

	~RTSGame();

	FRTSGameMode GameMode;

	RTSNation* GetNationByPlayer(uint8 PlayerID);

private:

	EGameStates GameState;

	RTSNation* Nations[RTS_NATION_MAX];
};
