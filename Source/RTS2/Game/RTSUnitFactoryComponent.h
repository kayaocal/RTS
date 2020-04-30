// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTS2/Prerequisites.h"
#include "RTSUnitFactoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS2_API URTSUnitFactoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSUnitFactoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame

	class RTSUnit* CreateUnit(EUnitTypes UnitType, const int PlayerIndex, const FVector& Position);
    class RTSUnit* CreateUnit(EUnitTypes UnitType, ENations Nation, EColors Color, const FVector& Position);
};
