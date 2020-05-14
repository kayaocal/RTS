// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "RTS2/Template/delegates.h"
#include "RTSButtonList.generated.h"


/**
 * 
 */
UCLASS()
class RTS2_API URTSButtonList : public UButton
{
	GENERATED_BODY()

	int ButtonIndex;
	UFUNCTION()
	void ButtonClickEvent();

	
	
	public:
	
	delegate<int> OnRTSButtonListClicked;
	
	URTSButtonList();
	~URTSButtonList();
	void SetButtonIndex(int index);
};
