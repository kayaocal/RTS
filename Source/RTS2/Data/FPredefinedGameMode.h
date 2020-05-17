#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RTS2/Game/RTSGameMode.h"
#include "FPredefinedGameMode.generated.h"

USTRUCT(BlueprintType)
struct RTS2_API FGameModeHolder
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRTSGameMode Mode;

};

USTRUCT(BlueprintType)
struct RTS2_API FPredefinedGameMode
    : public FTableRowBase
{
    GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ActiveGameModeIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGameModeHolder> GameModes;
};