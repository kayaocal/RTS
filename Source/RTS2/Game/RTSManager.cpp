#include "RTSManager.h"
#include "RTS2/Prerequisites.h"

RTSManager& RTSManager::GetInstance()
{
   static RTSManager Instance;
   return Instance; 

}

void RTSManager::InitializeDataTables()
{
    DataStore.PrepareGameDatas();
}

RTSManager::RTSManager()
{
	LOG_ERR("RTS MANAGER CREATED");
}

void RTSManager::CreateGame()
{
	if(Game == nullptr)
	{
		Game = new RTSGame();
	}
}

void RTSManager::DeleteGame()
{
	if(Game)
	{
		delete Game;
		Game = nullptr;
	}
}

RTSManager::~RTSManager()
{
}
