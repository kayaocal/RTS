// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTS2/Game/RTSPrimitiveResources.h"
#include "RTS2/Data/RTSPopulationData.h"
#include "FRTSNationIdentity.h"

/**
 * 
 */
 



class RTS2_API RTSNation
{

public:

	
	void OnBankUpdate(int Wood, int Food, int Gold);
	
	RTSNation(const FRTSNationIdentity &Identity);

	~RTSNation();

	/*
	*	All of the resources that nation has
	*/
	FRTSNationIdentity NationIdentity;
	RTSPrimitiveResources NationalBank;
	RTSPopulationData	  Population;
	bool IsResourcesDirty();

private:
	bool bIsResourcesDirty = false;

};
