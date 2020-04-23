

#pragma once

#include "CoreMinimal.h"

/**
 *	In game resources and payments 
 */
class RTS2_API RTSPrimitiveResources
{
	uint64 Gold;
	uint64 Wood;
	uint64 Food;

public:

	RTSPrimitiveResources();
	RTSPrimitiveResources(uint64 Gold, uint64 Wood, uint64 Food);
	~RTSPrimitiveResources();
	
	uint64 GetGold();
	uint64 GetWood();
	uint64 GetFood();
	void SetGold(uint64 GoldAmount);
	void SetWood(uint64 WoodAmount);
	void SetFood(uint64 FoodAmount);

	void operator = (RTSPrimitiveResources const &obj);

	void Add(RTSPrimitiveResources const &obj);

	bool Spend(RTSPrimitiveResources const &obj);

	bool IsAffordable(RTSPrimitiveResources const &obj);
	
	void operator + (RTSPrimitiveResources const &obj);

	RTSPrimitiveResources& operator += (RTSPrimitiveResources const &obj);

	bool operator - (RTSPrimitiveResources const &obj);

	RTSPrimitiveResources& operator -= (RTSPrimitiveResources const &obj);

};