// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGame.h"



RTSGame::RTSGame()
{
	GameState = EGameStates::Waiting;
	Nations[0] = new RTSNation(FRTSNationIdentity());
}

RTSGame::RTSGame(const FRTSGameMode& Mode)
{
	GameState = EGameStates::Waiting;
	GameMode = Mode;
}

RTSGame::~RTSGame()
{
}

RTSNation* RTSGame::GetNationByPlayer(uint8 PlayerID)
{
	return Nations[PlayerID];
}

