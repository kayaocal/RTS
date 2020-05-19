#pragma once
#include "CoreMinimal.h"
#include "RTSNation.h"
#include "UObject/ObjectMacros.h"
#include "RTS2/Prerequisites.h"
#include "FRTSNationIdentity.h"

#include "RTSGameMode.generated.h"

USTRUCT(BlueprintType)
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
	



	/*
	*	in terms of seconds
	*	-value means limitless.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int GameCountDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 NumberOfPlayers;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 MapID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EGamePlayType> GamePlayType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EGameMode> GameMode;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString GameName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FRTSNationIdentity> NationIdentities;
	
};

inline FRTSGameMode::FRTSGameMode(const FRTSGameMode & Mode)
{
	GameCountDown = Mode.GameCountDown;
	NumberOfPlayers = Mode.NumberOfPlayers;
	MapID = Mode.MapID;
	GameMode = Mode.GameMode;
	GamePlayType = Mode.GamePlayType;
	
	FRTSNationIdentity data{};
	data.bIsValid = false;
	NationIdentities.Init(data, RTS_NATION_MAX);
	
	if(Mode.NationIdentities.Num() > 0)
	{
		 for (int i = 0; i < RTS_NATION_MAX; i++)
		 {
			if(Mode.NationIdentities.IsValidIndex(i))
			{
				NationIdentities[i].SetNationForm(Mode.NationIdentities[i]);
			}
		 	else
		 	{
		 		NationIdentities[i].bIsValid = false;
		 	}
		 }
	}
}

inline FRTSGameMode::FRTSGameMode()
	:GameCountDown(0), NumberOfPlayers(0), MapID(0), GamePlayType(EGamePlayType::Campaign), GameMode(EGameMode::Classic)
{
	FRTSNationIdentity data{};
	data.bIsValid = false;
	NationIdentities.Init(data, RTS_NATION_MAX);
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