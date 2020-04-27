// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "RTS2/Game/RTSManager.h"

URTSGameInstance::URTSGameInstance()
	:UGameInstance()
{
	RTSManager::GetInstance().InitializeDataTables();
}

