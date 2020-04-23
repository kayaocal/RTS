// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "vector"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSNation.h"

/**
 *	Main Class of game.
 *	Game State, Players, Nations etc
 *	RTSGame class rule them all.
 */

class RTS2_API RTSGameMode
{

public:
private:

	/*
	*	in terms of seconds
	*	-value means limitless.
	*/
	uint64 GameCountDown;

	uint8 NumberOfPlayers;

	uint8 MapID;

	EGamePlayType GamePlayType;

	EGameMode GameMode;

};

class RTS2_API RTSGame
{

public:
	RTSGame(RTSGameMode* GameMode);

	~RTSGame();

	RTSNation* NationFactory(ENations Nation, FColor Color, EControllerType ControllerType, uint8 PlayerID);

	RTSNation* GetNationByPlayer(uint8 PlayerID);

private:

	EGameStates GameState;

	std::vector<RTSNation*> Players;

	RTSGameMode* GameMode;
};
