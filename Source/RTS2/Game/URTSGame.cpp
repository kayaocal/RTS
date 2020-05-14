// Fill out your copyright notice in the Description page of Project Settings.


#include "URTSGame.h"


URTSGameMode::URTSGameMode()
	:UObject(),
	GameCountDown(0), NumberOfPlayers(0), MapID(0), GamePlayType(EGamePlayType::Campaign), GameMode(EGameMode::Classic)
{

}

URTSGameMode::~URTSGameMode()
{
	
}

void URTSGameMode::SetRtsGameMode(const URTSGameMode& Mode)
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

URTSGame::URTSGame()
	:URTSGameMode()
{
	GameState = EGameStates::Waiting;
	Nations[0] = new RTSNation(RTSNationIdentity());
}

URTSGame::URTSGame(const URTSGameMode& GameMode)
	:URTSGameMode()
{
	GameState = EGameStates::Waiting;
	SetRtsGameMode(GameMode);
}

URTSGame::~URTSGame()
{
}

RTSNation* URTSGame::GetNationByPlayer(uint8 PlayerID)
{
	return Nations[PlayerID];
}

void URTSGameMode::SetGameCountDown(uint64 Value) 
{
	GameCountDown = Value;
}

void URTSGameMode::SetNumberOfPlayers(uint8 Value)
{
	NumberOfPlayers = Value;
}

void URTSGameMode::SetMapID(uint8 Value)
{
	MapID = Value;
}

void URTSGameMode::SetGamePlayType(EGamePlayType Value)
{
	GamePlayType = Value;
}

void URTSGameMode::SetGameMode(EGameMode Value)
{
	GameMode = Value;
}
