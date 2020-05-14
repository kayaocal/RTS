// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSetupWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UMultiplayerSetupWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ButtonSendClicked();
	
};
