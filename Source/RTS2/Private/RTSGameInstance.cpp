// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "RTS2/Game/RTSManager.h"

URTSGameInstance::URTSGameInstance()
	:UGameInstance()
{
	LOG_ERR("GAME INSTANCE INSTANTIATED");
	RTSManager::GetInstance();
	RTSManager::GetInstance().InitializeDataTables();
	RTSManager::GetInstance().CreateGame();
	
}

/*
 *	Cleaning stuff here.
 */
void URTSGameInstance::Shutdown()
{
	LOG_ERR("GAME INSTANCE SHUTDOWN");
	RTSManager::GetInstance().DeleteGame();
}

