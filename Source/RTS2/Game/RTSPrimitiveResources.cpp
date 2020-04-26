// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPrimitiveResources.h"


RTSPrimitiveResources::RTSPrimitiveResources()
{
	Gold = 0;
	Wood = 0;
	Food = 0;
}

RTSPrimitiveResources::RTSPrimitiveResources(int GoldAmount, int WoodAmount, int FoodAmount)
{
	Gold = GoldAmount;
	Wood = WoodAmount;
	Food = FoodAmount;
	OnResourceChanged.ExecuteIfBound(*this);
}

RTSPrimitiveResources::~RTSPrimitiveResources()
{
}

int RTSPrimitiveResources::GetGold() const
{
	return Gold;
}

int RTSPrimitiveResources::GetWood() const
{
	return Wood;
}

int RTSPrimitiveResources::GetFood() const
{
	return Food;
}

void RTSPrimitiveResources::SetGold(int GoldAmount)
{
	Gold = GoldAmount;
	OnResourceChanged.ExecuteIfBound(*this);
}

void RTSPrimitiveResources::SetWood(int WoodAmount)
{
	Wood = WoodAmount;
	OnResourceChanged.ExecuteIfBound(*this);
}

void RTSPrimitiveResources::SetFood(int FoodAmount)
{
	Food = FoodAmount;
	OnResourceChanged.ExecuteIfBound(*this);
}

void RTSPrimitiveResources::Add(FRTSPrimitiveResourceData const &obj)
{
	Gold += obj.Gold;
	Wood += obj.Wood;
	Food += obj.Food;
	OnResourceChanged.ExecuteIfBound(*this);
}

bool RTSPrimitiveResources::Spend(FRTSPrimitiveResourceData const & obj)
{
	if (IsAffordable(obj))
	{
		Gold -= obj.Gold;
		Wood -= obj.Wood;
		Food -= obj.Food;
		OnResourceChanged.ExecuteIfBound(*this);
		return true;
	}

	return false;
}

bool RTSPrimitiveResources::IsAffordable(FRTSPrimitiveResourceData const & obj) const
{
	return (Gold >= obj.Gold && Wood >= obj.Wood && Food >= obj.Food);
}

void RTSPrimitiveResources::operator+(FRTSPrimitiveResourceData const & obj)
{
	Add(obj);
}


bool RTSPrimitiveResources::operator-(FRTSPrimitiveResourceData const & obj)
{
	return Spend(obj);
}


void RTSPrimitiveResources::operator=(FRTSPrimitiveResourceData const & obj)
{
	Gold = obj.Gold;
	Wood = obj.Wood;
	Food = obj.Food;
}
