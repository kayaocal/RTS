// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RTS2_API DataStore
{
public:
	DataStore();
	~DataStore();

	struct FUnitDataRow* GetUnitConstructionDataRow(const FName& RowName) const;

private:

	void ReadUnitConstructionData();
	class UDataTable* UnitConstructionData;

};
