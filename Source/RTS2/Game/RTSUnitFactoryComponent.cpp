// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUnitFactoryComponent.h"

#include "RTS2/Public/GridManager.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Game/RTSManager.h"
#include "Kismet/GameplayStatics.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Public/RTSSkeletalActor.h"
#include "RTS2/Game/RTSNation.h"
#include "RTS2/Game/FRTSNationIdentity.h"
// Sets default values for this component's properties
URTSUnitFactoryComponent::URTSUnitFactoryComponent()
{

}


// Called when the game starts
void URTSUnitFactoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

RTSUnit* URTSUnitFactoryComponent::CreateUnit(EUnitTypes UnitType, const int PlayerIndex, const FVector& Position)
{
	return CreateUnit((EUnitTypes)UnitType, (ENations)RTS_NATION(PlayerIndex)->NationIdentity.Nation, RTS_NATION(PlayerIndex)->NationIdentity.Color, Position);
}

RTSUnit* URTSUnitFactoryComponent::CreateUnit(EUnitTypes UnitType, ENations Nation, EColors Color,
	const FVector& Position)
{
	RTSUnit *unit = new RTSUnit();
	FUnitDataRow* unitRow = RTS_DATA.GetUnitConstructionDataRow(UnitNames[UnitType]);
	
	if(UnitType == EUnitTypes::House)
	{
		RTS_NATION(0)->Population.AddLimit(10);	
	}
	
	if (unitRow == nullptr)
	{
		LOG_ERR("UnitRow is null!");
		return nullptr;
	}
	
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		
		if(unitRow->IsSkeletalMesh)
		{
			FString fstringVar = "MESH SKELETAl";
			UE_LOG(LogTemp, Warning, TEXT("Text,  %s"), *fstringVar );

			ARTSSkeletalActor* NewActor = GetWorld()->SpawnActor<ARTSSkeletalActor>(ARTSSkeletalActor::StaticClass(), Position, FRotator::ZeroRotator);
			unit->actor = NewActor;
			NewActor->SetMyUnit(unit);
			
			USkeletalMesh* SkeletalMesh = RTS_DATA.GetUnitSkeletalMesh((ENations)Nation, (EUnitTypes)UnitType);
			if(SkeletalMesh != nullptr)
			{
				NewActor->ItemSkeletalMesh->SetSkeletalMesh(SkeletalMesh);
			
			}
			UMaterialInterface* MeshMaterial = (UMaterialInterface*)RTS_DATA.GetUnitSkeletalMeshMaterial((ENations)Nation, (EUnitTypes)UnitType);
			
			if(MeshMaterial != nullptr)
			{
				NewActor->ItemSkeletalMesh->SetMaterial(0, MeshMaterial);
			}

			UAnimBlueprint* AnimBP = RTS_DATA.GetUnitSkeletalMeshAnimClass((ENations)Nation, (EUnitTypes)UnitType);
			if(AnimBP != nullptr)
			{
				//NewActor->ItemSkeletalMesh->SetAnimInstanceClass(AnimBP);
			}
			NewActor->SetGridScale(unitRow->GridSizeRow, unitRow->GridSizeCol);
		}
		else
		{
			ARTSStaticActor* NewActor = GetWorld()->SpawnActor<ARTSStaticActor>(ARTSStaticActor::StaticClass(), FVector(0,0,200), FRotator::ZeroRotator);
			if(NewActor != nullptr)
			{
				NewActor->SetActorLocation(Position, false);
				unit->actor = NewActor;
				NewActor->SetMyUnit(unit);
				
				NewActor->ItemStaticMesh->SetStaticMesh(RTS_DATA.GetUnitStaticMesh((ENations)Nation, (EUnitTypes)UnitType));
				NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)RTS_DATA.GetUnitStaticMeshMaterial((ENations)Nation, (EUnitTypes)UnitType));
				NewActor->SetGridScale(unitRow->GridSizeRow, unitRow->GridSizeCol);
			}
		}
	
	}

	unit->Color = Color;
	unit->Nation = Nation;
	unit->UnitType = UnitType;
	unit->GridColSize = unitRow->GridSizeCol;
	unit->GridRowSize = unitRow->GridSizeRow;

	if(PlayerController != nullptr)
	{
		PlayerController->GridSystem->PlaceUnit(unit, PlayerController->GridSystem->WorldToGrid(Position));
	}
	
	
	DestroyCommand* NewCommand = new DestroyCommand(unit);
	unit->UnitCommands.Add(NewCommand);

	if(unit->UnitType == EUnitTypes::BaseBuilding)
	{
		BuildCommand* SpawnSoldierCommand = new BuildCommand(unit,EUnitTypes::Soldier);
		unit->UnitCommands.Add(SpawnSoldierCommand);
	}
	
	return unit;
}

