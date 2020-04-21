#pragma once

/*
*		PLEASE FILL THIS CLASS WITH COMMON DATA TYPES, ENUMS, STRUCTS
* 
* */


#include "UObject/ObjectMacros.h"

#define LOG(txt) UE_LOG(LogTemp, Log, TEXT(txt) )
#define LOG_W(txt) UE_LOG(LogTemp, Warning, TEXT(txt) )
#define LOG_ERR(txt) UE_LOG(LogTemp, Error, TEXT(txt) )

UENUM(BlueprintType)
enum EControllerType
{
	Bot,
	Player
};

UENUM(BlueprintType)
enum EGameStates
{
	Waiting,
	Pause,
	Resuming
};

UENUM(BlueprintType)
enum EGamePlayType
{
	Campaign,
	Solo,
	Multiplayer
};

UENUM(BlueprintType)
enum EGameMode
{
	Classic,
	Raid
};

UENUM(BlueprintType)
enum EUnitTypes
{
	BaseBuilding		UMETA(DisplayName = "BASE BUILDING"),
	House				UMETA(DisplayName = "HOUSE"),
	BaseUnit			UMETA(DisplayName = "BASE UNIT"),
	Archer				UMETA(DisplayName = "ARCHER")
};

UENUM(BlueprintType)
enum ENations
{
	Any						UMETA(DisplayName = "ANY NATION",	ToolTip = "All Nations"),
	Group1					UMETA(DisplayName = "GROUP 1",		ToolTip = "Group One")
};