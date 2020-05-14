// Fill out your copyright notice in the Description page of Project Settings.


#include "MSetupUserSettingsRow.h"
#include "RTS2/Prerequisites.h"
#include "UiUtilities.h"

void UMSetupUserSettingsRow::BindUI()
{

	UiUtilities::SafeFillComboboxWColor(CBSPlayerColor);
	UiUtilities::SafeFillComboboxWNation(CBSPlayerNation);
	UiUtilities::SafeSetEditableText(ETPlayerName, FText::FromString(ANSI_TO_TCHAR("PLAYER_X")));
	BLPlayerStatus->SetBackgroundColor(RTSRedColor);
	
	
}
