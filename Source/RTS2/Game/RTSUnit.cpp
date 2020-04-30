// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUnit.h"

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
