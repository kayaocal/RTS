// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSNation.h"
#include "RTS2/Template/delegates.h"
#include "RTS2/Data/DataStore.h"
#include "RTS2/Game/RTSManager.h"
#include "RTS2/Data/FNationDefaultStats.h"

RTSNation::RTSNation(const FRTSNationIdentity& Identity)
{
	NationIdentity =  Identity;

	FNationDefaultStats* DefaultStats = RTS_DATA.GetNationDefaults(NationNames[Identity.Nation]);
	
	NationalBank.SetFood(DefaultStats->DefaultResourceAmount.Food);
	NationalBank.SetGold(DefaultStats->DefaultResourceAmount.Gold);
	NationalBank.SetWood(DefaultStats->DefaultResourceAmount.Wood);
	Population.SetLimit(DefaultStats->DefaultPopulation);
	Population.SetPopulation(0);
	NationalBank.OnResourceChanged.add<RTSNation, &RTSNation::OnBankUpdate>(this);
	
}

RTSNation::~RTSNation()
{
}

bool RTSNation::IsResourcesDirty()
{
	return bIsResourcesDirty;
	
}

void RTSNation::OnBankUpdate(int Wood, int Food, int Gold)
{
	bIsResourcesDirty = true;
	LOG("BANK IS DIRTY");
	
}

FRTSNationIdentity::FRTSNationIdentity()
{
}

FRTSNationIdentity::FRTSNationIdentity(const FRTSNationIdentity & Identity)
{
	SetNationForm(Identity);
	
}

FRTSNationIdentity::~FRTSNationIdentity()
{
}

void FRTSNationIdentity::SetNationForm(ENations NationEnum, EColors ColorValue, uint8 PlayersID, uint8 TeamsID, ENationControllerType Controller)
{
	this->TeamID = TeamsID;
	this->PlayerID = PlayersID;
	this->ControllerType = Controller;
	this->Color = ColorValue;
	this->Nation = NationEnum;
}

void FRTSNationIdentity::SetNationForm(const FRTSNationIdentity & NationIdentity)
{
	SetNationForm(NationIdentity.Nation, NationIdentity.Color, NationIdentity.PlayerID, NationIdentity.TeamID, NationIdentity.ControllerType);
}
