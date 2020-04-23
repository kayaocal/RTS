// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGame.h"

RTSGameMode::RTSGameMode(const RTSGameMode & Mode)
{
	GameCountDown = Mode.GameCountDown;
	NumberOfPlayers = Mode.NumberOfPlayers;
	MapID = Mode.MapID;
	GameMode = Mode.GameMode;
	GamePlayType = Mode.GamePlayType;

	for (int i = 0; i < RTS_NATION_MAX; i++)
	{
		NationIdentities[i].SetNationForm(Mode.NationIdentities[i]);
	}
}

RTSGame::RTSGame(const RTSGameMode& GameMode)
	:RTSGameMode(GameMode)
{
	GameState = EGameStates::Waiting;

}

void RTSGameMode::SetGameCountDown(uint64 Value)
{
	GameCountDown = Value;
}

void RTSGameMode::SetNumberOfPlayers(uint8 Value)
{
	NumberOfPlayers = Value;
}

void RTSGameMode::SetMapID(uint8 Value)
{
	MapID = Value;
}

void RTSGameMode::SetGamePlayType(EGamePlayType Value)
{
	GamePlayType = Value;
}

void RTSGameMode::SetGameMode(EGameMode Value)
{
	GameMode = Value;
}
