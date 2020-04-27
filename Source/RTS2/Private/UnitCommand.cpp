// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCommand.h"
#include "RTS2/RTSUnit.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "RTS2/Prerequisites.h"

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
