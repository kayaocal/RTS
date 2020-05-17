// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTSGameInstance.h"
#include "RTS2/Game/RTSGame.h"
#include "RTS2/Data/DataStore.h"

enum EGameExistance
{
	None,		//	Not decided yet
	QuickGame,	//	Directly gameplay 
	Game,		//	Start from Menu
	Illegal		//	Illegal game open
};

class RTSManager
{
public:
    
	URTSGameInstance *GameInstance = nullptr;
	AGameModeBase	*GameMode = nullptr;
	
	RTSGame 	*Game = nullptr;
	DataStore 	DataStore;

	EGameExistance Existance;
	
	static RTSManager& GetInstance();

	void InitializeDataTables();
	void CreateGame();
	void CreateGame(const FRTSGameMode& Mode);
	void DeleteGame();
	void SetGameMode(AGameModeBase* Mode);
	void SetGameExistance(EGameExistance Type);
private:
	
    RTSManager();
	~RTSManager();

	void CreateQuickGame();

};


