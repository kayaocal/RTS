#pragma once
#include "CoreMinimal.h"
#include "RTSNation.h"
#include "UObject/ObjectMacros.h"
#include "RTS2/Prerequisites.h"

#include "RTSGameMode.generated.h"

USTRUCT()
struct FRTSGameMode
{
	GENERATED_BODY()

	FRTSGameMode();
	FRTSGameMode(const FRTSGameMode& Mode);
	~FRTSGameMode();

	void SetGameCountDown(uint64 Value);
	

	void SetNumberOfPlayers(uint8 Value);
	

	void SetMapID(uint8 Value);
	

	void SetGamePlayType(EGamePlayType Value);
	

	void SetGameMode(EGameMode Value);
	


private:

	/*
	*	in terms of seconds
	*	-value means limitless.
	*/
	UPROPERTY()
	uint64 GameCountDown;
	UPROPERTY()
	uint8 NumberOfPlayers;
	UPROPERTY()
	uint8 MapID;
	UPROPERTY()
	TEnumAsByte<EGamePlayType> GamePlayType;
	UPROPERTY()
	TEnumAsByte<EGameMode> GameMode;

	FRTSNationIdentity NationIdentities[RTS_NATION_MAX];
};

inline FRTSGameMode::FRTSGameMode(const FRTSGameMode & Mode)
{
	GameCountDown = Mode.GameCountDown;
	NumberOfPlayers = Mode.NumberOfPlayers;
	MapID = Mode.MapID;
	GameMode = Mode.GameMode;
	GamePlayType = Mode.GamePlayType;

	for (int i = 0; i < RTS_NATION_MAX; i++)
	{
		NationIdentities[i].SetNationForm(Mode.NationIdentities[i]);
	}
}

inline FRTSGameMode::FRTSGameMode()
	:GameCountDown(0), NumberOfPlayers(0), MapID(0), GamePlayType(EGamePlayType::Campaign), GameMode(EGameMode::Classic)
{

}

inline FRTSGameMode::~FRTSGameMode()
{
}

inline void FRTSGameMode::SetGameCountDown(uint64 Value) 
{
	GameCountDown = Value;
}

inline void FRTSGameMode::SetNumberOfPlayers(uint8 Value)
{
	NumberOfPlayers = Value;
}

inline void FRTSGameMode::SetMapID(uint8 Value)
{
	MapID = Value;
}

inline void FRTSGameMode::SetGamePlayType(EGamePlayType Value)
{
	GamePlayType = Value;
}

inline void FRTSGameMode::SetGameMode(EGameMode Value)
{
	GameMode = Value;
}