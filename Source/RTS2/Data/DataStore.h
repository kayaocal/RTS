// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSPrimitiveResourceData.h"
#include "RTS2/Prerequisites.h"

/**
 * 
 */
class RTS2_API DataStore
{
public:
	DataStore();
	~DataStore();

	struct FUnitDataRow* GetUnitConstructionDataRow(const FName& RowName) const;
	struct FUnitNecessityRow* GetUnitNecessityRow(const FName& RowName) const;
	FRTSPrimitiveResourceData* GetUnitPrice(ENations NationType, EUnitTypes UnitType);
	class UStaticMesh* GetUnitStaticMesh(ENations NationType, EUnitTypes UnitType);
	class USkeletalMesh* GetUnitSkeletalMesh(ENations NationType, EUnitTypes UnitType);
	class UMaterialInstance* GetUnitSkeletalMeshMaterial(ENations NationType, EUnitTypes UnitType);
	class UMaterialInstance* GetUnitStaticMeshMaterial(ENations NationType, EUnitTypes UnitType);

private:

	void ReadUnitConstructionData();
	class UDataTable* UnitConstructionData;
	class UDataTable* UnitNecessitiesData;
	void ReadUnitNecessitiesData();
};
