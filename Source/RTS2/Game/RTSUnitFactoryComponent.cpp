// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUnitFactoryComponent.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Game/RTSManager.h"
#include "Kismet/GameplayStatics.h"
#include "RTS2/Public/RTSPlayerController.h"

// Sets default values for this component's properties
URTSUnitFactoryComponent::URTSUnitFactoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTSUnitFactoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URTSUnitFactoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

RTSUnit* URTSUnitFactoryComponent::CreateUnit(EUnitTypes UnitType, const int PlayerIndex, const FVector& Position)
{
	return CreateUnit((EUnitTypes)UnitType, (ENations)RTS_NATION(PlayerIndex)->Nation, RTS_NATION(PlayerIndex)->Color, Position);
}

RTSUnit* URTSUnitFactoryComponent::CreateUnit(EUnitTypes UnitType, ENations Nation, EColors Color,
	const FVector& Position)
{
	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(100, 100, 15);

	FUnitDataRow* unitRow = RTS_DATA.GetUnitConstructionDataRow(UnitNames[UnitType]);
	
	if (unitRow == nullptr)
	{
		LOG_ERR("UnitRow is null!");
		return nullptr;
	}
	
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), Position, FRotator::ZeroRotator);

		unit->actor = NewActor;
		NewActor->SetMyUnit(unit);
		if(unitRow->IsSkeletalMesh)
		{
			//NewActor->ItemStaticMesh->SkeletalMesh(RTS_GAME_INSTANCE->DataStore.GetUnitSkeletalMesh((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
			//NewActor->ItemStaticMesh->SetMaterial(RTS_GAME_INSTANCE->DataStore.GetUnitSkeletalMeshMaterial((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
		}
		else
		{
			NewActor->ItemStaticMesh->SetStaticMesh(RTS_DATA.GetUnitStaticMesh((ENations)Nation, (EUnitTypes)UnitType));
			NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)RTS_DATA.GetUnitStaticMeshMaterial((ENations)Nation, (EUnitTypes)UnitType));		
		}

	}

	DestroyCommand* NewCommand = new DestroyCommand(unit);

	unit->UnitCommands.Add(NewCommand);
	return unit;
}

