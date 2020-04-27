#include "RTSManager.h"


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
}

RTSManager::~RTSManager()
{
}
