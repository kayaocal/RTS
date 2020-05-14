// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS2/Game/URTSGame.h"
#include "RTS2/Data/DataStore.h"

class RTSManager
{
public:
    

	URTSGame 	*Game;
	DataStore 	DataStore;
	URTSGameMode GameModeSetting;

	static RTSManager& GetInstance();

	void InitializeDataTables();
	void CreateGame();
	void DeleteGame();
	
private:
	
    RTSManager();
	~RTSManager();

};


