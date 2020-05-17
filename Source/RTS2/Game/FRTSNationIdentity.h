#pragma once

#include "RTS2/Prerequisites.h"
#include "CoreMinimal.h"

#include "FRTSNationIdentity.generated.h"
/*
 *	Responsible of holding game setup datas
 */

USTRUCT(BlueprintType)
struct RTS2_API FRTSNationIdentity
{
	GENERATED_BODY()

	FRTSNationIdentity();
	FRTSNationIdentity(const FRTSNationIdentity& Identity);
	~FRTSNationIdentity();
	void SetNationForm(ENations NationEnum, EColors ColorValue, uint8 PlayersID, uint8 TeamsID,
	                   ENationControllerType Controller);

	void SetNationForm(const FRTSNationIdentity& NationIdentity);

	bool IsValidPlayer();
	
	/*
	*	Nation cannot change after game started
	*	It is necessary to create other gameplay modules
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ENations> Nation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EColors> Color;

	/*
	*	Bot or Gamer
	* */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ENationControllerType> ControllerType;
	
	/*
	*	Given ID to player. Used to identfy which player controls this nation.
	*	A player can be a Bot or a Gamer.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PlayerID;

	/*
	*	Natural Allies has same TeamID
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int TeamID;

	/*TODO: Connection datas such as ip...*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Nickname;


	/*
	 * If true : this is a valid player
	 * If false : this is empty player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsValid;

	
};
