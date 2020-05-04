// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "RTS2/Game/RTSManager.h"
#include "Engine.h"


URTSGameInstance::URTSGameInstance()
	:UGameInstance()
{
	LOG_ERR("GAME INSTANCE INSTANTIATED");
	RTSManager::GetInstance();
	RTSManager::GetInstance().InitializeDataTables();
	RTSManager::GetInstance().CreateGame();
	
}

//Only works on game start
void URTSGameInstance::Init()
{
	LOG_ERR("GAME INSTANCE Inited");

}

/*
 *	Cleaning stuff here.
 */
void URTSGameInstance::Shutdown()
{
	LOG_ERR("GAME INSTANCE SHUTDOWN");
	RTSManager::GetInstance().DeleteGame();
}

void URTSGameInstance::Host()
{

	UEngine* Engine = GetEngine();
	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/DebugLevel?listen");
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

