// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "CoreMinimal.h"
#include "RTS2/Public/RTSActor.h"
#include "RTS2/Public/UnitCommand.h"

/**
 * 
 */
class RTS2_API RTSUnit
{
private:
	bool bIsSelected;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARTSActor* actor;
	TArray<UnitCommand*> UnitCommands;
	EUnitTypes UnitType;
	ENations Nation;
	EColors Color;
	int GridRowSize;
	int GridColSize;
	int CenterGridIndex;

	void SetSelection(bool bIsSelected);


	RTSUnit();
	~RTSUnit();
};
