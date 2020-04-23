// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPrimitiveResources.h"

RTSPrimitiveResources::RTSPrimitiveResources()
{
	Gold = 0;
	Wood = 0;
	Food = 0;
}

RTSPrimitiveResources::RTSPrimitiveResources(uint64 Gold, uint64 Wood, uint64 Food)
	:Gold(Gold), Wood(Wood), Food(Food)
{
}

RTSPrimitiveResources::~RTSPrimitiveResources()
{
}

uint64 RTSPrimitiveResources::GetGold()
{
	return Gold;
}

uint64 RTSPrimitiveResources::GetWood()
{
	return Wood;
}

uint64 RTSPrimitiveResources::GetFood()
{
	return Food;
}

void RTSPrimitiveResources::SetGold(uint64 GoldAmount)
{
	Gold = GoldAmount;
}

void RTSPrimitiveResources::SetWood(uint64 WoodAmount)
{
	Wood = WoodAmount;
}

void RTSPrimitiveResources::SetFood(uint64 FoodAmount)
{
	Food = FoodAmount;
}

void RTSPrimitiveResources::Add(RTSPrimitiveResources const &obj)
{
	Gold += obj.Gold;
	Wood += obj.Wood;
	Food += obj.Food;
}

bool RTSPrimitiveResources::Spend(RTSPrimitiveResources const & obj)
{
	if (IsAffordable(obj))
	{
		Gold -= obj.Gold;
		Wood -= obj.Wood;
		Food -= obj.Food;

		return true;
	}

	return false;
}

bool RTSPrimitiveResources::IsAffordable(RTSPrimitiveResources const & obj)
{
	return (Gold >= obj.Gold && Wood >= obj.Wood && Food >= obj.Food);
}

void RTSPrimitiveResources::operator+(RTSPrimitiveResources const & obj)
{
	Add(obj);
}

RTSPrimitiveResources & RTSPrimitiveResources::operator+=(RTSPrimitiveResources const & obj)
{
	Add(obj);
	return *this;
}

bool RTSPrimitiveResources::operator-(RTSPrimitiveResources const & obj)
{
	return Spend(obj);
}

RTSPrimitiveResources & RTSPrimitiveResources::operator-=(RTSPrimitiveResources const & obj)
{
	Spend(obj);
	return *this;
}

void RTSPrimitiveResources::operator=(RTSPrimitiveResources const & obj)
{
	Gold = obj.Gold;
	Wood = obj.Wood;
	Food = obj.Food;
}
