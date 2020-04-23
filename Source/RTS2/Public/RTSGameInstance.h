// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RTS2/Game/RTSGame.h"

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

	class UDataTable* UnitConstructionData;

	void ReadUnitConstructionData();
	struct FUnitDataRow* GetUnitConstructionDataRow(const FName& RowName) const;

};
