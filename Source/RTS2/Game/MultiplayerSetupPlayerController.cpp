// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerSetupPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/GameMode/MultiplayerLobbyGameMode.h"

AMultiplayerSetupPlayerController::AMultiplayerSetupPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

void AMultiplayerSetupPlayerController::SayHiRPC_Implementation(const FRPCData2& data)
{
	LOG_ERR("Controller this time");
	LOG_ERR("Server Send Message : %hs ",  *data.message);
	LOG_ERR("Server Send Message : %d ", data.age);
	LetsPlay();
}

bool AMultiplayerSetupPlayerController::SayHiRPC_Validate(const FRPCData2& data)
{
	return true;
}

void AMultiplayerSetupPlayerController::LetsPlay_Implementation()
{
	LOG_W("Player wants to play!!");

	((AMultiplayerLobbyGameMode*)UGameplayStatics::GetGameMode(this))->PlayerIsRead(1);
	
}
