// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCommand.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"
#include "RTS2/Game/RTSManager.h"
#include "RTS2/Game/RTSUnitFactoryComponent.h"

UnitCommand::UnitCommand()
{
}

UnitCommand::~UnitCommand()
{
}

DestroyCommand::DestroyCommand(class RTSUnit* Receiver)
{
	MyUnit = Receiver;
}

DestroyCommand::~DestroyCommand()
{
}

void DestroyCommand::Execute()
{
	if (MyUnit != nullptr && MyUnit->actor != nullptr)
	{
		ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(MyUnit->actor, 0));
		if (PlayerController != nullptr)
		{
			PlayerController->ClearSelectedActors();
		}

		delete MyUnit;
	}
}

BuildCommand::BuildCommand(RTSUnit* Receiver, EUnitTypes UnitToSpawn, FVector UnitOffset)
{
	MyUnit = Receiver;
	UnitType = UnitToSpawn;
	SpawnOffset = UnitOffset;
}

BuildCommand::~BuildCommand()
{
}

void BuildCommand::Execute()
{
	if (MyUnit != nullptr && MyUnit->actor != nullptr)
	{
		FRTSPrimitiveResourceData* UnitPrice = RTS_DATA.GetUnitPrice(MyUnit->Nation, UnitType);
		if(IS_RTS_NATION_EXIST(0))
		{
			if(RTS_NATION(0)->NationalBank.Spend(*UnitPrice) == false)
			{
				return;
			}
		}
		ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(MyUnit->actor, 0));
		if (PlayerController != nullptr)
		{
			RTSUnit* NewUnit =  PlayerController->UnitFactory->CreateUnit(UnitType,  MyUnit->Nation, MyUnit->Color, MyUnit->actor->GetActorLocation()+SpawnOffset);
		}
	}
}

