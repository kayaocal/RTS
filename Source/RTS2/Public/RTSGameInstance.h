// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"

#include "RTSGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class RTS2_API URTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public :

	IOnlineSessionPtr SessionInterface;
	FName SessionName = TEXT("My UI Session");

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	URTSGameInstance();

	virtual void Init() override;
	
	virtual void Shutdown() override;


	void FindSession();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Adress);


	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete( bool Success);

	void CreateSession();

};



