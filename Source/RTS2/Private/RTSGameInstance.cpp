// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "RTS2/Game/RTSManager.h"
#include "Engine.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

URTSGameInstance::URTSGameInstance()
	:UGameInstance()
{
	LOG_ERR("GAME INSTANCE INSTANTIATED");
	

}

//Only works on game start
void URTSGameInstance::Init()
{

	RTSManager::GetInstance();
	RTSManager::GetInstance().GameInstance = this;
	RTSManager::GetInstance().InitializeDataTables();
	RTSManager::GetInstance().Existance = EGameExistance::None;
	
	LOG_ERR("GAME INSTANCE Inited");
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if(Subsystem != nullptr)
	{
		LOG_W("Found Subsytem %s", *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			LOG_W("Found Session Interface ");
			
			// SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnCreateSessionComplete);
			// SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnDestroySessionComplete);
			// SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &URTSGameInstance::OnFindSessionComplete);
			//
			// SessionSearch = MakeShareable(new FOnlineSessionSearch());
			// if(SessionSearch.IsValid())
			// {
			// 	SessionSearch->bIsLanQuery = true;
			// 	LOG_W("Start to find sessions");
			// 	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			// }
			// else
			// {
			// 		// Ayni Session isminde baska session var. O sessioni kapat
			// 	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SessionName);
			// 	if(ExistingSession != nullptr)
			// 	{
			// 		LOG_W("DestorySession %s", *SessionName.ToString());
			// 		SessionInterface->DestroySession(SessionName);
			// 	}
			// 	else
			// 	{
			// 		CreateSession();
			// 	}
			// }
			
		}
	}
	else
	{
		LOG_ERR("Can not find Subsytem");
	}
}

/*
 *	Cleaning stuff here.
 */
void URTSGameInstance::Shutdown()
{
	LOG_ERR("GAME INSTANCE SHUTDOWN");
	RTSManager::GetInstance().DeleteGame();
}

void URTSGameInstance::FindSession()
{
	if(SessionInterface.IsValid())
	{
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if(SessionSearch.IsValid())
		{
			SessionSearch->bIsLanQuery = true;
			LOG_W("Start to find sessions from menu");
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void URTSGameInstance::Host()
{

	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;
	FString MapStr(MapNames[EMap::DebugLevel]);
	MapStr.Append("?listen");
	World->ServerTravel(MapStr);
}

void URTSGameInstance::OnDestroySessionComplete(FName Name, bool Success)
{
	if(Success)
	{
		LOG_W("Session Succesfully Destroyed");
		CreateSession();
	}
	else
	{
		LOG_ERR("Session Destroy failed");
	}	
}

void URTSGameInstance::OnFindSessionComplete(bool Success)
{
	if(Success)
	{
		LOG_W("Session found successfully");
		if(SessionSearch.IsValid())
		{
			for(const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
			{
				LOG_W("Found Session name : %s ", *SearchResult.GetSessionIdStr());
			}
		}
	}
	else
	{
		LOG_W("Session cannot be found");
	}
}

void URTSGameInstance::CreateSession()
{
	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SessionName);
	if(ExistingSession != nullptr)
	{
		LOG_W("DestorySession %s", *SessionName.ToString());
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnDestroySessionComplete);
		SessionInterface->DestroySession(SessionName);
		return;
	}
	
	LOG_W("CreateSession()");
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 2;
	SessionSettings.bShouldAdvertise = true;
	
	SessionInterface->CreateSession(0, SessionName, SessionSettings);
}

void URTSGameInstance::OnCreateSessionComplete(FName Name, bool Success)
{
	if(!Success)
	{
		LOG_ERR("Session could not created!");
		return;
	}
	
	LOG_W("Session succesfully created!");
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	FString MapStr(MapNames[EMap::MultiplayerGameSetup]);
	MapStr.Append("?listen");
	World->ServerTravel(MapStr);
}

void URTSGameInstance::Join(const FString& Adress)
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, FString::Printf(TEXT("Joining to %s..."), *Adress));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Adress, ETravelType::TRAVEL_Absolute);
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, FString::Printf(TEXT("Travelling")));
	
}



