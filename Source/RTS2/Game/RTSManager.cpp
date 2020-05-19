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

void RTSManager::CreateGame(const FRTSGameMode& Mode)
{
	if(Game == nullptr)
	{
		Game = new RTSGame(Mode);
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

void RTSManager::SetGameMode(AGameModeBase* Mode)
{
	GameMode = Mode;
}

void RTSManager::SetGameExistance(EGameExistance Type)
{
	if(Existance == EGameExistance::None)
	{
		Existance = Type;
		if(Existance == EGameExistance::QuickGame)
		{
			LOG("Game Existance is QuickGame");
			CreateQuickGame();
		}
		else if(Existance == EGameExistance::Game)
		{
			LOG("Game Existance is Game");
			
		}
	}
	else
	{
		LOG_ERR("GameExistance already assigned to %d", Existance);
	}
}

RTSManager::~RTSManager()
{
}

void RTSManager::CreateQuickGame()
{
	LOG("Create Quick Game");
	FRTSGameMode* Mode = DataStore.GetDefaultGameMode();
	ensureMsgf(Mode != nullptr, TEXT("DataStore.GetDefaultGameMode() returned null"));
	if(Mode)
	{
		LOG_ERR("Mode is not null");
		CreateGame(*Mode);
	}
	else
	{
		LOG_ERR("Mode is null");
	}

	
}
