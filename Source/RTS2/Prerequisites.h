#pragma once

/*
*		PLEASE FILL THIS CLASS WITH COMMON DATA TYPES, ENUMS, STRUCTS
* 
* */


#include "UObject/ObjectMacros.h"

#define LOG(txt, ...) UE_LOG(LogTemp, Log, TEXT(txt), __VA_ARGS__)
#define LOG_W(txt, ...) UE_LOG(LogTemp, Warning, TEXT(txt), __VA_ARGS__)
#define LOG_ERR(txt, ...) UE_LOG(LogTemp, Error, TEXT(txt), __VA_ARGS__)

#define RTS_GAME_INSTANCE Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))

#define RTS_GAME					RTSManager::GetInstance().Game
#define RTS_DATA					RTSManager::GetInstance().DataStore
#define RTS_NATION(Index)			RTSManager::GetInstance().Game->GetNationByPlayer(Index)
#define IS_RTS_NATION_EXIST(Index) 	(RTS_GAME && RTS_NATION(Index))
#define RTS_NATION_MAX 8


UENUM(BlueprintType)
enum EMap
{
	MainMenu		= 0,
	DebugMap		= 1
};

UENUM(BlueprintType)
enum EControllerType
{
	Bot,
	Player
};

UENUM(BlueprintType)
enum  EGameStates
{
	Menu,
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

//------------------ UNIT TYPES ------------------->>>
UENUM(BlueprintType)
enum EUnitTypes
{
	BaseBuilding		=0			UMETA(DisplayName = "BaseBuilding"),
	House				=1			UMETA(DisplayName = "House"),
	Library			 	=2			UMETA(DisplayName = "Library"),
	Tomb				=3			UMETA(DisplayName = "Tomb"),
	Soldier				=4			UMETA(DisplayName = "Soldier"),



	EUnitTypeCounter									
};

#define UNIT_TYPE_COUNT 5

/*
 * UnitNames Order and Size must be same with EUnitTypes enum
 */
const char UnitNames[UNIT_TYPE_COUNT][40]
{
	"BaseBuilding",					//0
	"House",						//1
	"Library",						//2
	"Tomb",							//3
	"Soldier"						//4
};

//------------------ UNIT TYPES -------------------<<<
//------------------- NATIONS -------------------->>>

UENUM(BlueprintType)
enum ENations
{
	Any						= 0		UMETA(DisplayName = "ANY NATION",	ToolTip = "All Nations"),
	Nation1					= 1		UMETA(DisplayName = "Nation 1",		ToolTip = "Nation One"),	
	Nation2					= 2		UMETA(DisplayName = "Nation 2",		ToolTip = "Nation Two"),	
	Nation3					= 3		UMETA(DisplayName = "Nation 3",		ToolTip = "Nation Three")
}; 

#define NATION_COUNT 4

/*
* NationNames Order and Size must be same with ENations enum
*/
const char NationNames[UNIT_TYPE_COUNT][40]
{
	"AllNations",					// 0
    "Nation1",						// 1
    "Nation2",						// 1
    "Nation3"						// 1
};

//------------------- NATIONS --------------------<<<

//------------------- COLORS -------------------->>>

UENUM(BlueprintType)
enum EColors
{
	Red						= 0		UMETA(DisplayName = "Red",			ToolTip = "Red"),
	Green					= 1		UMETA(DisplayName = "Green",		ToolTip = "Green"),	
	Blue					= 2		UMETA(DisplayName = "Blue",			ToolTip = "Blue"),	
	Yellow					= 3		UMETA(DisplayName = "Yellow",		ToolTip = "Yellow")
}; 

#define COLOR_COUNT 4
const char ColorNames[UNIT_TYPE_COUNT][40]
{
	"Red",
    "Green",
	"Blue",
	"Yellow"
};

//------------------- COLORS --------------------<<<

UENUM(BlueprintType)
enum DataTableEnums
{
	UnitConstructionDataTable = 0
};
