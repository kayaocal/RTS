#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"
#include "FUnitNecessityRow.generated.h"

USTRUCT(BlueprintType)

struct RTS2_API FUnitNecessity
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<ENations> Nation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRTSPrimitiveResourceData ResourceData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, META = (DisplayName = "Unit Population"))
		int UnitPopulation;


};

USTRUCT(BlueprintType)
struct FUnitNecessityRow
    : public FTableRowBase
{
    GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EUnitTypes> UnitType;

	int test;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FUnitNecessity> Necessities;
};
