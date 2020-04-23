// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"


/**
 * 
 */
UCLASS()
class RTS2_API ARTSHud : public AHUD
{
	GENERATED_BODY()
private:

	bool bSelectionActive = false;

public:
	FVector2D SelectionStartPoint;
	FVector2D SelectionEndPoint;

	virtual void DrawHUD() override;

	void StartSelecting();
	void StopSelecting();
	FVector2D GetMousePos2D();
	FLinearColor SelectionColor = FLinearColor(0,1,0,0.2f);
	
};
