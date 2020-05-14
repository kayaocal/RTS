// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUnit.h"


#include "RTSPlayerController.h"
#include "RTS2/Public/GridManager.h"
#include "Kismet/GameplayStatics.h"

void RTSUnit::SetSelection(bool bSelected)
{
	if (actor == nullptr)
	{
		return;
	}
	bIsSelected = bSelected;
	actor->SetSelection(bIsSelected);
}

RTSUnit::RTSUnit()
{
}

RTSUnit::~RTSUnit()
{


	
	if (actor != nullptr)
	{
		ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(actor, 0));
		if(PlayerController!=nullptr)
		{
			if(PlayerController->GridSystem != nullptr)
			{
				PlayerController->GridSystem->RemoveUnit(this);
			}
		}
		actor->Destroy(false, true);
	}

	int i = 0;

	for (i = 0; i < UnitCommands.Num(); i++)
	{
		if (UnitCommands[i] != nullptr)
		{
			delete UnitCommands[i];
		}
	}
}
