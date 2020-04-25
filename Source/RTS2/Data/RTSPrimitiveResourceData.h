// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSPrimitiveResourceData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct RTS2_API FRTSPrimitiveResourceData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Wood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Gold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Food;
};
