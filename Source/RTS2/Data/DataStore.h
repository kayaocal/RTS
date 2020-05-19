// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSActor.h"
#include "RTSPrimitiveResourceData.h"
#include "Animation/AnimBlueprint.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSGameMode.h"

/**
 * 
 */
class RTS2_API DataStore
{
public:
	DataStore();
	~DataStore();

	
	FRTSGameMode* GetDefaultGameMode() const;
	FRTSGameMode* GetRTSGameModeFromGameInfo(int Index) const;
	struct FNationDefaultStats* GetNationDefaults(const FName& RowName) const;
	struct FUnitDataRow* GetUnitConstructionDataRow(const FName& RowName) const;
	struct FUnitNecessityRow* GetUnitNecessityRow(const FName& RowName) const;
	
	FRTSPrimitiveResourceData* GetUnitPrice(ENations NationType, EUnitTypes UnitType);
	void SetRTSActorSMeshAndMaterial(ARTSActor& Actor, ENations NationType, EUnitTypes UnitType, EColors Color);
	class UStaticMesh* GetUnitStaticMesh(ENations NationType, EUnitTypes UnitType);
	class USkeletalMesh* GetUnitSkeletalMesh(ENations NationType, EUnitTypes UnitType);
	class UMaterialInstance* GetUnitSkeletalMeshMaterial(ENations NationType, EUnitTypes UnitType);
	UAnimBlueprint* GetUnitSkeletalMeshAnimClass(ENations NationType, EUnitTypes UnitType);
	class UMaterialInstance* GetUnitStaticMeshMaterial(ENations NationType, EUnitTypes UnitType);
	void PrepareGameDatas();

private:

	void ReadNationDefaults();
	void ReadUnitConstructionData();
	void ReadUnitNecessitiesData();
	void ReadGameInfoData();
	
	class UDataTable* UnitConstructionData;
	class UDataTable* UnitNecessitiesData;
	class UDataTable* NationDefaultsData;
	class UDataTable* DefaultGameModesData;
};
