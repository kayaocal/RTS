// Fill out your copyright notice in the Description page of Project Settings.


#include "DataStore.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Data/FUnitNecessityRow.h"
#include "RTS2/Data/FNationDefaultStats.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTS2/Public/RTSStaticActor.h"

DataStore::DataStore()
{

}

DataStore::~DataStore()
{
}

void DataStore::ReadNationDefaults()
{
	FSoftObjectPath UnitDataTablePath = FSoftObjectPath(TEXT("DataTable'/Game/Data/NationDefaultStats.NationDefaultStats'"));
	NationDefaultsData = Cast<UDataTable>(UnitDataTablePath.ResolveObject());
	
	if (NationDefaultsData == nullptr)
	{
		NationDefaultsData = Cast<UDataTable>(UnitDataTablePath.TryLoad());
	}
}

FNationDefaultStats* DataStore::GetNationDefaults(const FName& RowName) const
{
	if (NationDefaultsData == nullptr)
	{
		return nullptr;
	}

	return NationDefaultsData->FindRow<FNationDefaultStats>(RowName, TEXT(""));
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

void DataStore::SetRTSActorSMeshAndMaterial(ARTSActor& Actor, ENations NationType, EUnitTypes UnitType, EColors Color)
{
	if((Cast<ARTSStaticActor>(&Actor))->ItemStaticMesh == nullptr)
	{
		return;
	}
	(Cast<ARTSStaticActor>(&Actor))->ItemStaticMesh->SetStaticMesh(GetUnitStaticMesh(NationType, UnitType));
	(Cast<ARTSStaticActor>(&Actor))->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)GetUnitStaticMeshMaterial(NationType, UnitType));
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
		if(Row->NationStaticMeshData[i].Nation == NationType && Row->NationStaticMeshData[i].MeshByAge.Num() > 0)
		{
			return Row->NationStaticMeshData[i].MeshByAge[0];
		}

		if(Row->NationStaticMeshData[i].Nation == ENations::Any && Row->NationStaticMeshData[i].MeshByAge.Num() > 0)
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
	for(int i = 0; i < Row->NationSkeletalMeshData.Num(); i++)
	{
			
		if(Row->NationSkeletalMeshData[i].Nation == NationType && Row->NationSkeletalMeshData[i].MeshByAge.Num()>0)
		{
			return Row->NationSkeletalMeshData[i].MeshByAge[0];
		}

		if(Row->NationSkeletalMeshData[i].Nation == ENations::Any && Row->NationSkeletalMeshData[i].MeshByAge.Num()>0)
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
	for(int i = 0; i < Row->NationSkeletalMeshData.Num(); i++)
	{
		if(Row->NationSkeletalMeshData[i].Nation == NationType && Row->NationSkeletalMeshData[i].MaterialsByAge.Num()>0)
		{
			return Row->NationSkeletalMeshData[i].MaterialsByAge[0];
		}

		if(Row->NationSkeletalMeshData[i].Nation == ENations::Any && Row->NationSkeletalMeshData[i].MaterialsByAge.Num()>0)
		{
			Material = Row->NationSkeletalMeshData[i].MaterialsByAge[0]; 
		}
	}
	
	return Material;	
}

UAnimBlueprint* DataStore::GetUnitSkeletalMeshAnimClass(ENations NationType, EUnitTypes UnitType)
{
	if(UnitType >= EUnitTypes::EUnitTypeCounter || UnitType < 0)
	{
		return nullptr;	
	}
	FUnitDataRow* Row = GetUnitConstructionDataRow(UnitNames[UnitType]);
	UAnimBlueprint* AnimClass = nullptr;
	for(int i = 0; i < Row->NationSkeletalMeshData.Num(); i++)
	{
		if(Row->NationSkeletalMeshData[i].Nation == NationType)
		{
			return Row->NationSkeletalMeshData[i].AnimationBP;
		}

		if(Row->NationSkeletalMeshData[i].Nation == ENations::Any)
		{
			AnimClass = Row->NationSkeletalMeshData[i].AnimationBP;
		}
	}
	
	return AnimClass;	
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
		if(Row->NationStaticMeshData[i].Nation == NationType && Row->NationStaticMeshData[i].MaterialsByAge.Num() > 0)
		{
			return Row->NationStaticMeshData[i].MaterialsByAge[0];
		}

		if(Row->NationStaticMeshData[i].Nation == ENations::Any && Row->NationStaticMeshData[i].MaterialsByAge.Num() > 0)
		{
			Material = Row->NationStaticMeshData[i].MaterialsByAge[0]; 
		}
	}
	
	return Material;	
}

void DataStore::PrepareGameDatas()
{
	ReadUnitConstructionData();
	ReadUnitNecessitiesData();
	ReadNationDefaults();
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
