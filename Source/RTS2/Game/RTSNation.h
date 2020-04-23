// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSPrimitiveResources.h"

/**
 * 
 */
class RTS2_API RTSNation
{

public:

	RTSNation(ENations Nation, FColor Color, EControllerType ControllerType, uint8 PlayerID);

	~RTSNation();

private:

	/*
	*	Nation cannot change after game started
	*	It is necessary to create other gameplay modules
	*/
	ENations Nation;

	FColor Color;

	/*
	*	Given ID to player. Used to identfy which player controls this nation.
	*	A player can be a Bot or a Gamer.
	*/
	uint8 PlayerID;

	/*
	*	Natural Allies has same TeamID
	*/
	uint8 TeamID;

	/*
	*	Bot or Gamer
	*/
	EControllerType ControllerType;

	RTSPrimitiveResources NationBank;

};
