// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "RTS2/UI/RTSButtonList.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

	class URTSGameInstance* GameInstance = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MultiplayerSubMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* HostSettingsSubMenu = nullptr;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ServerListSubMenu = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* MainPageCanvas = nullptr;
	

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtHeader;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtServerListSearching;

	UPROPERTY(meta = (BindWidget))
	UButton* BtJoin;

	UPROPERTY(meta = (BindWidget))
	UButton* BtHost;
	
	TArray<URTSButtonList*> FoundServerList;

	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ButtonMultiplayerClicked();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ButtonHostClicked();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ButtonJoinClicked();
	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ButtonCreateGameClicked();

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnFindSessionComplete(bool Success);
	void OnCreateSessionComplete(FName Name, bool Success);
	FDelegateHandle FindSessionDelegateHandler;
	FDelegateHandle CreateSessionDelegateHandler;
	FDelegateHandle JoinSessionDelegateHandler;

	void OnJoinToServerButtonClicked(int Index);

	void ClearServerListButtons();	
};
