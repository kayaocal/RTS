// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSNation.h"


RTSNation::RTSNation(const RTSNationIdentity& Identity)
	:RTSNationIdentity(Identity)
{
}

RTSNation::~RTSNation()
{
}

RTSNationIdentity::RTSNationIdentity()
{
}

RTSNationIdentity::RTSNationIdentity(const RTSNationIdentity & Identity)
{
	SetNationForm(Identity);
}

RTSNationIdentity::~RTSNationIdentity()
{
}

void RTSNationIdentity::SetNationForm(ENations NationEnum, const FColor & ColorValue, uint8 PlayersID, uint8 TeamsID, EControllerType Controller)
{
	this->TeamID = TeamsID;
	this->PlayerID = PlayersID;
	this->ControllerType = Controller;
	this->Color = ColorValue;
	this->Nation = NationEnum;
}

void RTSNationIdentity::SetNationForm(const RTSNationIdentity & NationIdentity)
{
	SetNationForm(NationIdentity.Nation, NationIdentity.Color, NationIdentity.PlayerID, NationIdentity.TeamID, NationIdentity.ControllerType);
}
