// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTS2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API ARTS2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARTS2GameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay() override;
	void CreateUI();
};
