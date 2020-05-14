// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS2/Game/RTSGame.h"
#include "RTS2/Data/DataStore.h"

class RTSManager
{
public:
    

	RTSGame 	*Game;
	DataStore 	DataStore;
	FRTSGameMode GameModeSetting;

	static RTSManager& GetInstance();

	void InitializeDataTables();
	void CreateGame();
	void DeleteGame();
	
private:
	
    RTSManager();
	~RTSManager();

};


