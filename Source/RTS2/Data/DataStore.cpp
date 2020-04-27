// Fill out your copyright notice in the Description page of Project Settings.


#include "DataStore.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Data/FUnitNecessityRow.h"

DataStore::DataStore()
{
	ReadUnitConstructionData();
	ReadUnitNecessitiesData();
}

DataStore::~DataStore()
{
}

void DataStore::ReadUnitConstructionData()
{
	FSoftObjectPath UnitDataTablePath = FSoftObjectPath(TEXT("DataTable'/Game/Data/Unit/UnitConstruction.UnitConstruction'"));
	UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.ResolveObject());
	
	if (UnitConstructionData == nullptr)
	{
		UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.TryLoad());
	}
}

void DataStore::ReadUnitNecessitiesData()
{
	FSoftObjectPath UnitDataTablePath = FSoftObjectPath(TEXT("DataTable'/Game/Data/Unit/UnitNecessity.UnitNecessity'"));
	UnitNecessitiesData = Cast<UDataTable>(UnitDataTablePath.ResolveObject());
	
	if (UnitNecessitiesData == nullptr)
	{
		UnitNecessitiesData = Cast<UDataTable>(UnitDataTablePath.TryLoad());
	} 
}

FUnitNecessityRow* DataStore::GetUnitNecessityRow(const FName& RowName) const
{
	if (UnitNecessitiesData == nullptr)
	{
		return nullptr;
	}

	return UnitNecessitiesData->FindRow<FUnitNecessityRow>(RowName, TEXT(""));
}

FRTSPrimitiveResourceData* DataStore::GetUnitPrice(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitNecessityRow* Row = GetUnitNecessityRow(UnitNames[UnitType]);
	FRTSPrimitiveResourceData* ResourceData = nullptr;
	for(int i = 0; i < Row->Necessities.Num(); i++)
	{
		if(Row->Necessities[i].Nation == NationType)
		{
			return &Row->Necessities[i].ResourceData;
		}

		if(Row->Necessities[i].Nation == ENations::Any)
		{
			ResourceData = &Row->Necessities[i].ResourceData; 
		}
	}
	
	return ResourceData;	
}

UStaticMesh* DataStore::GetUnitStaticMesh(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitDataRow* Row = GetUnitConstructionDataRow(UnitNames[UnitType]);
	UStaticMesh* StaticMesh = nullptr;
	for(int i = 0; i < Row->NationStaticMeshData.Num(); i++)
	{
		if(Row->NationStaticMeshData[i].Nation == NationType)
		{
			return Row->NationStaticMeshData[i].MeshByAge[0];
		}

		if(Row->NationStaticMeshData[i].Nation == ENations::Any)
		{
			StaticMesh = Row->NationStaticMeshData[i].MeshByAge[0]; 
		}
	}
	
	return StaticMesh;	
}

USkeletalMesh* DataStore::GetUnitSkeletalMesh(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitDataRow* Row = GetUnitConstructionDataRow(UnitNames[UnitType]);
	USkeletalMesh* SkeletalMesh = nullptr;
	for(int i = 0; i < Row->NationStaticMeshData.Num(); i++)
	{
		if(Row->NationSkeletalMeshData[i].Nation == NationType)
		{
			return Row->NationSkeletalMeshData[i].MeshByAge[0];
		}

		if(Row->NationSkeletalMeshData[i].Nation == ENations::Any)
		{
			SkeletalMesh = Row->NationSkeletalMeshData[i].MeshByAge[0]; 
		}
	}
	
	return SkeletalMesh;	
}

UMaterialInstance* DataStore::GetUnitSkeletalMeshMaterial(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitDataRow* Row = GetUnitConstructionDataRow(UnitNames[UnitType]);
	UMaterialInstance* Material = nullptr;
	for(int i = 0; i < Row->NationStaticMeshData.Num(); i++)
	{
		if(Row->NationSkeletalMeshData[i].Nation == NationType)
		{
			return Row->NationSkeletalMeshData[i].MaterialsByAge[0];
		}

		if(Row->NationSkeletalMeshData[i].Nation == ENations::Any)
		{
			Material = Row->NationSkeletalMeshData[i].MaterialsByAge[0]; 
		}
	}
	
	return Material;	
}

UMaterialInstance* DataStore::GetUnitStaticMeshMaterial(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitDataRow* Row = GetUnitConstructionDataRow(UnitNames[UnitType]);
	UMaterialInstance* Material = nullptr;
	for(int i = 0; i < Row->NationStaticMeshData.Num(); i++)
	{
		if(Row->NationStaticMeshData[i].Nation == NationType)
		{
			return Row->NationStaticMeshData[i].MaterialsByAge[0];
		}

		if(Row->NationStaticMeshData[i].Nation == ENations::Any)
		{
			Material = Row->NationStaticMeshData[i].MaterialsByAge[0]; 
		}
	}
	
	return Material;	
}

FUnitDataRow* DataStore::GetUnitConstructionDataRow(const FName& RowName) const
{
	if (UnitConstructionData == nullptr)
	{
		LOG_ERR("NULL GetUnitConstructionDataRow ^");
		return nullptr;
	}
	return UnitConstructionData->FindRow<FUnitDataRow>(RowName, TEXT(""));
}
