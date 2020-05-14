// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "vector"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSNation.h"

#include "URTSGame.generated.h"

/**
 *	Main Class of game.
 *	Game State, Players, Nations etc
 *	RTSGame class rule them all.
 */


UCLASS(Blueprintable)
class RTS2_API URTSGameMode
	:public UObject
{
	GENERATED_BODY()

public:

	URTSGameMode();
	~URTSGameMode();

	void SetRtsGameMode(const URTSGameMode& Mode);
	
	void SetGameCountDown(uint64 Value);
	

	void SetNumberOfPlayers(uint8 Value);
	

	void SetMapID(uint8 Value);
	

	void SetGamePlayType(EGamePlayType Value);
	

	void SetGameMode(EGameMode Value);
	


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

	RTSNationIdentity NationIdentities[RTS_NATION_MAX];
};

UCLASS(Blueprintable)
class RTS2_API URTSGame : public URTSGameMode
{
	GENERATED_BODY()

public:

	URTSGame();
	URTSGame(const URTSGameMode& GameMode);

	~URTSGame();


	RTSNation* GetNationByPlayer(uint8 PlayerID);

private:

	EGameStates GameState;

	RTSNation* Nations[RTS_NATION_MAX];
};
