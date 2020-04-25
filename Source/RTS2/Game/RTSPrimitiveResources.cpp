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
}

void RTSPrimitiveResources::SetWood(int WoodAmount)
{
	Wood = WoodAmount;
}

void RTSPrimitiveResources::SetFood(int FoodAmount)
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

bool RTSPrimitiveResources::IsAffordable(RTSPrimitiveResources const & obj) const
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
