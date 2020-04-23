// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "CoreMinimal.h"

/**
 * 
 */
class RTS2_API RTSUnit
{
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ARTSActor* actor;

	RTSUnit();
	~RTSUnit();
};
