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

UENUM(BlueprintType)
enum class EUnitTypes : uint8
{
	BaseBuilding		UMETA(DisplayName = "BASE BUILDING"),
	House				UMETA(DisplayName = "HOUSE"),
	BaseUnit			UMETA(DisplayName = "BASE UNIT"),
	Archer				UMETA(DisplayName = "ARCHER")
};

UENUM(BlueprintType)
enum class ENations :uint8
{
	Any						UMETA(DisplayName = "ANY NATION",	ToolTip = "All Nations"),
	Group1					UMETA(DisplayName = "GROUP 1",		ToolTip = "Group One")
}; 

UENUM(BlueprintType)
enum DataTableEnums
{
	UnitConstructionDataTable = 0
};
