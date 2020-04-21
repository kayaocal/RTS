// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSNation.h"


RTSNation::RTSNation(ENations Nation, FColor Color, EControllerType ControllerType, uint8 PlayerID)
	: Nation(Nation), Color(Color), ControllerType(ControllerType), PlayerID(PlayerID)
{
}

RTSNation::~RTSNation()
{
}
