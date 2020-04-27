// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RTS2\Prerequisites.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"

#include "UnitDataRow.generated.h"
/**
 * 
 */
 
USTRUCT(BlueprintType)
struct RTS2_API FUnitSkeletalMeshData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<ENations> Nation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class USkeletalMesh*> MeshByAge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UMaterialInstance*> MaterialsByAge;
};

USTRUCT(BlueprintType)
struct RTS2_API FUnitStaticMeshData 
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<ENations> Nation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 TArray<class UStaticMesh*> MeshByAge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 TArray<class UMaterialInstance*> MaterialsByAge;
};

USTRUCT(BlueprintType)
struct RTS2_API FUnitDataRow : public FTableRowBase
{
	 GENERATED_BODY();

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 TEnumAsByte<EUnitTypes> UnitTpe;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 bool IsSkeletalMesh;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 TArray<FUnitStaticMeshData> NationStaticMeshData;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 TArray<FUnitSkeletalMeshData> NationSkeletalMeshData;

};
