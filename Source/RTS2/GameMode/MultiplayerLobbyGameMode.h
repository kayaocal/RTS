// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTS2/Connection/MultiplayerSetupConnActor.h"
#include "RTS2/Game/RTSGame.h"
#include "MultiplayerLobbyGameMode.generated.h"


/**
 * 
 */



UCLASS()
class RTS2_API AMultiplayerLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	FRTSGameMode GameModeSettings;

	int ControllerCount = 0;
	class AMultiplayerSetupPlayerController* array[5];
	
	AMultiplayerLobbyGameMode();

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void Logout(AController* Exiting) override;
	
	void PlayerIsRead(int PlayerIndex);

};
