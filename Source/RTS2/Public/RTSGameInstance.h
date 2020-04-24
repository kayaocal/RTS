// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RTS2/Game/RTSGame.h"
#include "RTS2/Data/DataStore.h"

#include "RTSGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class RTS2_API URTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public :

	URTSGameInstance();

	RTSGameMode GameModeSetting;

	RTSGame Game;

	DataStore DataStore;




};
