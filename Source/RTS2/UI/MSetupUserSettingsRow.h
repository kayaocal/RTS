// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSButtonList.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"

#include "MSetupUserSettingsRow.generated.h"


/**
 * 
 */
UCLASS()
class RTS2_API UMSetupUserSettingsRow : public UUserWidget
{
	GENERATED_BODY()
public:

	EPlayerLobbyStatus PlayerStatus;
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* ETPlayerName;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* CBSPlayerColor;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* CBSPlayerNation;

	UPROPERTY(meta = (BindWidget))
	URTSButtonList* BLPlayerStatus;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock*	TPlayerStatus;

	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void BindUI();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void UpdatePlayerStatusButton();
	
};
