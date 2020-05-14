// Fill out your copyright notice in the Description page of Project Settings.


#include "MSetupUserSettingsRow.h"
#include "RTS2/Prerequisites.h"
#include "UiUtilities.h"

void UMSetupUserSettingsRow::BindUI()
{
	UiUtilities::SafeFillComboboxWColor(CBSPlayerColor);
	UiUtilities::SafeFillComboboxWNation(CBSPlayerNation);
	UiUtilities::SafeSetEditableText(ETPlayerName, FText::FromString(ANSI_TO_TCHAR("PLAYER_X")));
	PlayerStatus = EPlayerLobbyStatus::Connecting;
	UpdatePlayerStatusButton();
}

void UMSetupUserSettingsRow::UpdatePlayerStatusButton()
{
	switch (PlayerStatus)
	{
		case EPlayerLobbyStatus::Connecting:
			BLPlayerStatus->SetBackgroundColor(GOrangeColor);
			UiUtilities::SafeSetTextBlock(TPlayerStatus, FText::FromString(ANSI_TO_TCHAR("Connecting")));
		break;
		case EPlayerLobbyStatus::Ready:
			BLPlayerStatus->SetBackgroundColor(GGreenColor);
			UiUtilities::SafeSetTextBlock(TPlayerStatus, FText::FromString(ANSI_TO_TCHAR("Ready")));
		break;
		case EPlayerLobbyStatus::NotReady:
		default:
			BLPlayerStatus->SetBackgroundColor(GRedColor);
			UiUtilities::SafeSetTextBlock(TPlayerStatus, FText::FromString(ANSI_TO_TCHAR("Waiting")));
		break;
		
	}
}


