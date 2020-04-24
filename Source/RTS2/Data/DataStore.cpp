// Fill out your copyright notice in the Description page of Project Settings.


#include "DataStore.h"
#include "RTS2/Data/UnitDataRow.h"

DataStore::DataStore()
{
	ReadUnitConstructionData();
}

DataStore::~DataStore()
{
}

void DataStore::ReadUnitConstructionData()
{
	FSoftObjectPath UnitDataTablePath = FSoftObjectPath(TEXT("DataTable'/Game/Data/UnitConstructionData.UnitConstructionData'"));
	UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.ResolveObject());

	if (UnitConstructionData == nullptr)
	{
		UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.TryLoad());
	}
}

FUnitDataRow* DataStore::GetUnitConstructionDataRow(const FName& RowName) const
{
	if (UnitConstructionData == nullptr)
	{
		return nullptr;
	}

	return UnitConstructionData->FindRow<FUnitDataRow>(RowName, TEXT(""));
}