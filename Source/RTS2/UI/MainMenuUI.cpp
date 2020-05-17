// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"

#include "UiUtilities.h"
#include "RTS2/Prerequisites.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "RTS2/Public/RTSGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Windows/LiveCoding/Private/External/LC_ClientCommandThread.h"
#include "Engine.h"

bool UMainMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	GameInstance = Cast<URTSGameInstance>( UGameplayStatics::GetGameInstance(this));

	UiUtilities::SafeSetVisibility(MultiplayerSubMenu, ESlateVisibility::Hidden);
	UiUtilities::SafeSetVisibility(HostSettingsSubMenu, ESlateVisibility::Hidden);
	UiUtilities::SafeSetVisibility(ServerListSubMenu, ESlateVisibility::Hidden);
	UiUtilities::SafeSetVisibility(MainPageCanvas, ESlateVisibility::Visible);


	return true;
}

void UMainMenuUI::ButtonMultiplayerClicked()
{
	UiUtilities::SafeSetVisibility(MultiplayerSubMenu, ESlateVisibility::Visible);
}

void UMainMenuUI::ButtonHostClicked()
{
	UiUtilities::SafeSetVisibility(HostSettingsSubMenu, ESlateVisibility::Visible);
	UiUtilities::SafeSetVisibility(ServerListSubMenu, ESlateVisibility::Hidden);
	UiUtilities::SafeSetIsEnabled(BtHost, false);
	UiUtilities::SafeSetIsEnabled(BtJoin, false);
	CreateSessionDelegateHandler = GameInstance->SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, & UMainMenuUI::OnCreateSessionComplete);
	GameInstance->CreateSession();
}

void UMainMenuUI::ButtonJoinClicked()
{
	UiUtilities::SafeSetVisibility(HostSettingsSubMenu, ESlateVisibility::Hidden);
	UiUtilities::SafeSetVisibility(ServerListSubMenu, ESlateVisibility::Visible);
	
	TxtServerListSearching->SetText(FText::FromString(TEXT("Searching...")));
	UiUtilities::SafeSetVisibility(TxtServerListSearching, ESlateVisibility::Visible);
	UiUtilities::SafeSetIsEnabled(BtHost, false);
	UiUtilities::SafeSetIsEnabled(BtJoin, false);
	FindSessionDelegateHandler = GameInstance->SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, & UMainMenuUI::OnFindSessionComplete);
	GameInstance->FindSession();
}


void UMainMenuUI::ButtonCreateGameClicked()
{
	if(GameInstance)
	{
		
	}
	else
	{
		LOG_ERR("CreateGame GameInstance is nullptr");
	}
}

void UMainMenuUI::OnFindSessionComplete(bool Success)
{
	LOG_W("YAAAY FIND SESSION WORKS");
	if(Success)
	{
		LOG_W("SUCCESS");
	}
	GameInstance->SessionInterface->OnFindSessionsCompleteDelegates.Remove(FindSessionDelegateHandler);
	UiUtilities::SafeSetIsEnabled(BtJoin, true);
	UiUtilities::SafeSetIsEnabled(BtHost, true);
	
	if(Success == false)
	{
		TxtServerListSearching->SetText(FText::FromString(TEXT("Failed...")));
	}
	UiUtilities::SafeSetVisibility(TxtServerListSearching, ESlateVisibility::Hidden);

	if(GameInstance->SessionSearch.IsValid())
	{
		LOG_W("SessionSearch is VALID and count : %d", GameInstance->SessionSearch->SearchResults.Num());
		
		
		for(int i = 0; i <  GameInstance->SessionSearch->SearchResults.Num(); i++)
		{
			const FOnlineSessionSearchResult& SearchResult =  GameInstance->SessionSearch->SearchResults[i];
			LOG_W("Found Session name : %s ", *SearchResult.GetSessionIdStr());
			URTSButtonList* button =  WidgetTree->ConstructWidget<URTSButtonList>(URTSButtonList::StaticClass(),  FName("BtSession"));
			button->SetButtonIndex(i);
			button->OnRTSButtonListClicked.add<UMainMenuUI, &UMainMenuUI::OnJoinToServerButtonClicked>(this);
			button->SetDisplayLabel(*SearchResult.GetSessionIdStr());
			FoundServerList.Add(button);			
			ServerListSubMenu->AddChild(button);
		}
		
	}
}

void UMainMenuUI::OnCreateSessionComplete(FName Name, bool Success)
{
	LOG_W("YAAAY CREATE SESSION WORKS %s ", *Name.ToString());
	if(Success)
	{
		LOG_W("Successfull");
	}
	
	GameInstance->SessionInterface->OnCreateSessionCompleteDelegates.Remove(CreateSessionDelegateHandler);
	UiUtilities::SafeSetIsEnabled(BtHost, true);
	UiUtilities::SafeSetIsEnabled(BtJoin, true);

	UEngine* Engine = GameInstance->GetEngine();
	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Hosting..."));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;
	FString MapStr(MapNames[EMap::MultiplayerGameSetup]);
	MapStr.Append("?listen");
	World->ServerTravel(MapStr);
}

void UMainMenuUI::OnJoinToServerButtonClicked(int Index)
{
	LOG_W("UMainMenuUI::OnJoinToServerButtonClicked %d ", Index);
	JoinSessionDelegateHandler = GameInstance->SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, & UMainMenuUI::OnJoinSessionComplete);
	GameInstance->SessionInterface->JoinSession(0, GameInstance->SessionName, GameInstance->SessionSearch->SearchResults[Index]);
	UiUtilities::SafeSetIsEnabled(BtHost, false);
	UiUtilities::SafeSetIsEnabled(BtJoin, false);
}

void UMainMenuUI::ClearServerListButtons()
{
	for(int i = 0; i < FoundServerList.Num(); i++)
	{
		ServerListSubMenu->RemoveChild(FoundServerList[i]);
		WidgetTree->RemoveWidget(FoundServerList[i]);
		URTSButtonList* btn = FoundServerList[i];
		btn->ConditionalBeginDestroy();
	}

	FoundServerList.Empty();
}


void UMainMenuUI::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	LOG_W("OnJoinSessionComplete");
	GameInstance->SessionInterface->OnJoinSessionCompleteDelegates.Remove(JoinSessionDelegateHandler);
	UiUtilities::SafeSetIsEnabled(BtHost, true);
	UiUtilities::SafeSetIsEnabled(BtJoin, true);
	
	if(Result != EOnJoinSessionCompleteResult::Success)
	{
		if(Result == EOnJoinSessionCompleteResult::AlreadyInSession)
		{
		}
		
		UEngine* Engine = GameInstance->GetEngine();
		if(!ensure(Engine != nullptr))
		{
			Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Join Session Failed... %d"), Result);
		}

	
		return;
	}

	LOG_W("Successfully Joined");
	UEngine* Engine = GameInstance->GetEngine();
	if(!ensure(Engine != nullptr))
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Purple, TEXT("Successfully Joined..."));
	}
	APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController();
	FString Adress;
	if(GameInstance->SessionInterface->GetResolvedConnectString(SessionName, Adress))
	{
		LOG_W("Adress : %s", *Adress);
		PlayerController->ClientTravel(Adress, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		LOG_ERR("Getting Adress is failed ");
	}
}
