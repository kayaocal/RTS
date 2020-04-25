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
		class USkeletalMesh* Construcion1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* Construcion2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* Construcion3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* ReadyMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USkeletalMesh* ReadyMesh3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UMaterialInstance* Material;
};


USTRUCT(BlueprintType)
struct RTS2_API FUnitStaticMeshData 
{
	GENERATED_BODY();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* Construcion1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* Construcion2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* Construcion3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* ReadyMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* ReadyMesh3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UMaterialInstance* Material;
};

USTRUCT(BlueprintType)
struct RTS2_API FUnitNecessity
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<ENations> Nation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRTSPrimitiveResourceData ResourceData;

};

USTRUCT(BlueprintType)
struct RTS2_API FUnitDataRow : public FTableRowBase
{
	 GENERATED_BODY();

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 int32 UnitId;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 TEnumAsByte<EUnitTypes> UnitType;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 TArray<FUnitNecessity> NecessityByNation;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
		 bool IsSkeletalMesh;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 FUnitStaticMeshData StaticMeshData;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 FUnitSkeletalMeshData SkeletalMeshData;

};
