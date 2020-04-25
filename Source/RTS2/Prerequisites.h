#pragma once

/*
*		PLEASE FILL THIS CLASS WITH COMMON DATA TYPES, ENUMS, STRUCTS
* 
* */


#include "UObject/ObjectMacros.h"

#define LOG(txt) UE_LOG(LogTemp, Log, TEXT(txt) )
#define LOG_W(txt) UE_LOG(LogTemp, Warning, TEXT(txt) )
#define LOG_ERR(txt) UE_LOG(LogTemp, Error, TEXT(txt) )

#define RTS_GAME_INSTANCE Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))
#define RTS_DATA_STORE &(Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->DataStore)

#define RTS_NATION_MAX 8

UENUM(BlueprintType)
enum class EMap : uint8
{
	MainMenu		= 0,
	DebugMap		= 1
};

UENUM(BlueprintType)
enum class EControllerType : uint8
{
	Bot,
	Player
};

UENUM(BlueprintType)
enum class EGameStates : uint8
{
	Menu,
	Waiting,
	Pause,
	Resuming
};

UENUM(BlueprintType)
enum class EGamePlayType : uint8
{
	Campaign,
	Solo,
	Multiplayer
};

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	Classic,
	Raid
};

//------------------ UNIT TYPES ------------------->>>
UENUM(BlueprintType)
enum EUnitTypes
{
	BaseBuilding		UMETA(DisplayName = "BASE BUILDING"),
	House				UMETA(DisplayName = "HOUSE"),
	BaseUnit			UMETA(DisplayName = "BASE UNIT"),
	Archer				UMETA(DisplayName = "ARCHER")
};

#define UNIT_TYPE_COUNT 4
/*
 * UnitNames Order and Size must be same with EUnitTypes enum
 */
const char UnitNames[UNIT_TYPE_COUNT][40]
{
	"BaseBuilding",
	"House",
	"BaseUnit",
	"Archer"	
};
//------------------ UNIT TYPES -------------------<<<
//------------------- NATIONS -------------------->>>
UENUM(BlueprintType)
enum ENations
{
	Any						UMETA(DisplayName = "ANY NATION",	ToolTip = "All Nations"),
	Group1					UMETA(DisplayName = "GROUP 1",		ToolTip = "Group One")
}; 

#define NATION_COUNT 2
/*
* NationNames Order and Size must be same with ENations enum
*/
const char NationNames[UNIT_TYPE_COUNT][40]
{
	"AllNations",
    "Group1"
};
//------------------- NATIONS --------------------<<<

//------------------- COLORS -------------------->>>

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
