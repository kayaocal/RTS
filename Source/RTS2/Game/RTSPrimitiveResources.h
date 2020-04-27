

#pragma once

#include "CoreMinimal.h"
#include "RTS2/Template/ObserverTemplate.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"

/**
 *	In game resources and payments 
 */
class RTS2_API RTSPrimitiveResources : public FRTSPrimitiveResourceData
{

public:

	RTSPrimitiveResources();
	RTSPrimitiveResources(int Gold, int Wood, int Food);
	~RTSPrimitiveResources();

	/** Called when any resource amount is changed. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	OnResourceChangedEvent OnResourceChanged;
	
	int GetGold() const;
	int GetWood() const;
	int GetFood() const;
	void SetGold(int GoldAmount);
	void SetWood(int WoodAmount);
	void SetFood(int FoodAmount);

	void operator = (FRTSPrimitiveResourceData const &obj);

	void Add(FRTSPrimitiveResourceData const &obj);

	bool Spend(FRTSPrimitiveResourceData const &obj);

	bool IsAffordable(FRTSPrimitiveResourceData const &obj) const;
	
	void operator + (FRTSPrimitiveResourceData const &obj);

	bool operator - (FRTSPrimitiveResourceData const &obj);

};

