#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"
#include "FNationDefaultStats.generated.h"

USTRUCT(BlueprintType)
struct FNationDefaultStats
	: public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ENations> Nation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int DefaultPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRTSPrimitiveResourceData DefaultResourceAmount;
};
