// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSPrimitiveResources.h"

/**
 * 
 */
 
 /*
 *	Responsible of holding game setup datas
 */
class RTS2_API RTSNationIdentity
{

public :

	RTSNationIdentity();
	RTSNationIdentity(const RTSNationIdentity& Identity);
	~RTSNationIdentity();
	void SetNationForm(ENations NationEnum, EColors ColorValue, uint8 PlayersID, uint8 TeamsID,
	                   EControllerType Controller);

	void SetNationForm(const RTSNationIdentity& NationIdentity);
	
	/*
	*	Nation cannot change after game started
	*	It is necessary to create other gameplay modules
	*/
	ENations Nation;

	EColors Color;

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
	* */
	EControllerType ControllerType;

	/*TODO: Connection datas such as ip...*/
	
};


class RTS2_API RTSNation : public RTSNationIdentity
{

public:

	RTSNation(const RTSNationIdentity &Identity);

	~RTSNation();

	/*
	*	All of the resources that nation has
	*/
	RTSPrimitiveResources NationalBank;





};
