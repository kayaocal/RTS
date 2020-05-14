#pragma once

#include "RTS2/Prerequisites.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "FRTSNationIdentity.generated.h"
/*
 *	Responsible of holding game setup datas
 */
USTRUCT()
struct RTS2_API FRTSNationIdentity
{
	GENERATED_BODY()
public :

	FRTSNationIdentity();
	FRTSNationIdentity(const FRTSNationIdentity& Identity);
	~FRTSNationIdentity();
	void SetNationForm(ENations NationEnum, EColors ColorValue, uint8 PlayersID, uint8 TeamsID,
	                   ENationControllerType Controller);

	void SetNationForm(const FRTSNationIdentity& NationIdentity);
	
	/*
	*	Nation cannot change after game started
	*	It is necessary to create other gameplay modules
	*/
	UPROPERTY()
	TEnumAsByte<ENations> Nation;

	UPROPERTY()
	TEnumAsByte<EColors> Color;

	/*
	*	Bot or Gamer
	* */
	UPROPERTY()
	TEnumAsByte<ENationControllerType> ControllerType;
	
	/*
	*	Given ID to player. Used to identfy which player controls this nation.
	*	A player can be a Bot or a Gamer.
	*/
	UPROPERTY()
	uint8 PlayerID;

	/*
	*	Natural Allies has same TeamID
	*/
	UPROPERTY()
	uint8 TeamID;



	/*TODO: Connection datas such as ip...*/

	UPROPERTY()
	FString Nickname;
};
