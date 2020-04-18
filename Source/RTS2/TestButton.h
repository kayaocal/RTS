// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "TestButton.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UTestButton : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void buttonEvent();
		
	
};
