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

#define RTS_GAME						RTSManager::GetInstance().Game
#define RTS_DATA						RTSManager::GetInstance().DataStore
#define RTS_NATION(Index)				RTSManager::GetInstance().Game->GetNationByPlayer(Index)
#define RTS_POPULATION(Index)			RTS_NATION(Index)->Population.GetPopulation()
#define RTS_POPULATION_LIMIT(Index)		RTS_NATION(Index)->Population.GetLimit()
#define IS_RTS_NATION_EXIST(Index) 		(RTS_GAME && RTS_NATION(Index))
#define RTS_NATION_MAX 8



UENUM(BlueprintType)
enum EMap
{
	MainMenu		= 0,
	DebugMap		= 1
};

UENUM(BlueprintType)
enum ENationControllerType
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

/*
 *	EPlayerLobbyStatus enum is used in multiplayer game setup scene
 *	to check if players are ready to start game
 */
UENUM(BlueprintType)
enum EPlayerLobbyStatus
{
	Connecting,
	NotReady,
	Ready
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

#define UNIT_TYPE_COUNT EUnitTypes::EUnitTypeCounter

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
	Nation3					= 3		UMETA(DisplayName = "Nation 3",		ToolTip = "Nation Three"),

	NationCount
}; 

#define NATION_COUNT ENations::NationCount

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
	Green					= 0		UMETA(DisplayName = "Green",		ToolTip = "Green"),
	Red						= 1		UMETA(DisplayName = "Red",			ToolTip = "Red"),	
	Orange					= 2		UMETA(DisplayName = "Orange",		ToolTip = "Orange"),	
	Yellow					= 3		UMETA(DisplayName = "Yellow",		ToolTip = "Yellow"),
	Blue					= 4		UMETA(DisplayName = "Blue",			ToolTip = "Blue"),
	Turquoise				= 5		UMETA(DisplayName = "Turquoise",	ToolTip = "Turquoise"),
	Purple					= 6		UMETA(DisplayName = "Purple",		ToolTip = "Purple"),

	ColorCount
}; 

#define COLOR_COUNT EColors::ColorCount
const char ColorNames[COLOR_COUNT][40]
{
	"Green",
    "Red",
	"Orange",
	"Yellow",
	"Blue",
	"Turquoise",
	"Purple"
};

/*
 *	Colors are taken from https://flatuicolors.com/palette/defo
 */
static const FColor GGreenColor			{46 , 204, 113, 255};
static const FColor GRedColor			{192, 57 , 43 , 255};
static const FColor GOrangeColor		{243, 156, 18 , 255};
static const FColor GYellowColor		{241, 196, 15 , 255};
static const FColor GBlueColor			{41 , 128, 185, 255};
static const FColor GTurquoiseColor		{26 , 188, 156, 255};
static const FColor GPurpleColor		{155, 89 , 182, 255};
static const FColor GDarkBlueColor		{44 , 62 , 80 , 255};

static const FLinearColor GGreenLinearColor			{GGreenColor};
static const FLinearColor GRedLinearColor			{GRedColor};
static const FLinearColor GOrangeLinearColor		{GOrangeColor};
static const FLinearColor GYellowLinearColor		{GYellowColor};
static const FLinearColor GBlueLinearColor			{GBlueColor};
static const FLinearColor GTurquoiseLinearColor		{GTurquoiseColor};
static const FLinearColor GPurpleLinearColor		{GPurpleColor};
static const FLinearColor GDarkBlueLinearColor		{GDarkBlueColor};

static const FColor* GGetColor[COLOR_COUNT]
{
	&GGreenColor,
	&GRedColor,
	&GOrangeColor,
	&GYellowColor,
	&GBlueColor,
	&GTurquoiseColor,
	&GPurpleColor
};

static const FLinearColor* GGetLinearColor[COLOR_COUNT]
{
	& GGreenLinearColor,
	& GRedLinearColor,
	& GOrangeLinearColor,
	& GYellowLinearColor,
	& GBlueLinearColor,
	& GTurquoiseLinearColor,
	& GPurpleLinearColor
};


//------------------- COLORS --------------------<<<
