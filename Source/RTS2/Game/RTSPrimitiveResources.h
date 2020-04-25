

#pragma once

#include "CoreMinimal.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"
/**
 *	In game resources and payments 
 */
 
class RTS2_API RTSPrimitiveResources : FRTSPrimitiveResourceData
{

public:

	RTSPrimitiveResources();
	RTSPrimitiveResources(int Gold, int Wood, int Food);
	~RTSPrimitiveResources();
	
	int GetGold() const;
	int GetWood() const;
	int GetFood() const;
	void SetGold(int GoldAmount);
	void SetWood(int WoodAmount);
	void SetFood(int FoodAmount);

	void operator = (RTSPrimitiveResources const &obj);

	void Add(RTSPrimitiveResources const &obj);

	bool Spend(RTSPrimitiveResources const &obj);

	bool IsAffordable(RTSPrimitiveResources const &obj) const;
	
	void operator + (RTSPrimitiveResources const &obj);

	RTSPrimitiveResources& operator += (RTSPrimitiveResources const &obj);

	bool operator - (RTSPrimitiveResources const &obj);

	RTSPrimitiveResources& operator -= (RTSPrimitiveResources const &obj);

};