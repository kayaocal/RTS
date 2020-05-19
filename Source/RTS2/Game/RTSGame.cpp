// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGame.h"



RTSGame::RTSGame()
{
	GameState = EGameStates::Waiting;
}

RTSGame::RTSGame(const FRTSGameMode& Mode)
{
	GameState = EGameStates::Waiting;
	GameMode = new FRTSGameMode(Mode);

	for(int i = 0; i < RTS_NATION_MAX; i++)
	{
		if(GameMode->NationIdentities[i].IsValidPlayer())
		{
			Nations[i] = new RTSNation(GameMode->NationIdentities[i]);
		}
		else
		{
			Nations[i] = nullptr;
		}
	}
}

RTSGame::~RTSGame()
{
	for(int i = 0; i < RTS_NATION_MAX; i++)
	{
		if(Nations[i] != nullptr)
		{
			delete Nations[i];
			Nations[i] = nullptr;
		}
	}
}

RTSNation* RTSGame::GetNationByPlayer(const uint8 PlayerID)
{
	return Nations[PlayerID];
}

