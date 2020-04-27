#include "RTSManager.h"

RTSManager& RTSManager::GetInstance()
{
    if(RTSManager::Instance == nullptr)
    {
        RTSManager::Instance = new RTSManager();
    }

    return *RTSManager::Instance;
}

void RTSManager::InitializeDataTables()
{
    DataStore.PrepareGameDatas();
    
}

RTSManager::RTSManager()
{
}

RTSManager::~RTSManager()
{
}
