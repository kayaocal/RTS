// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RTSHud.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTS2/Public/RTSPlayerController.h"

void ARTSHud::DrawHUD()
{
	if (bSelectionActive)
	{
		float MouseX;
		float MouseY;
		ARTSPlayerController* MyController = Cast<ARTSPlayerController>(GetOwningPlayerController());
		if (MyController == nullptr)
		{
			return;
		}
		MyController->GetMousePosition(MouseX, MouseY);
		SelectionEndPoint = FVector2D(MouseX, MouseY);

		float Width = SelectionEndPoint.X - SelectionStartPoint.X;
		float Height = SelectionEndPoint.Y - SelectionStartPoint.Y;

		DrawRect(SelectionColor, SelectionStartPoint.X, SelectionStartPoint.Y, Width, Height);
	
		MyController->SetSelectedActors(SelectionStartPoint, SelectionEndPoint);
	}
}

void ARTSHud::StartSelecting()
{
	bSelectionActive = true;
	float MouseX = 0;
	float MouseY = 0;
	APlayerController* MyController = GetOwningPlayerController();
	if (MyController != nullptr)
	{
		MyController->GetMousePosition(MouseX, MouseY);
	}
	SelectionStartPoint = FVector2D(MouseX, MouseY);
}

void ARTSHud::StopSelecting()
{
	bSelectionActive = false; 
}

FVector2D ARTSHud::GetMousePos2D()
{
	float MouseX = 0;
	float MouseY = 0;
	APlayerController* MyController = GetOwningPlayerController();
	if (MyController != nullptr)
	{
		MyController->GetMousePosition(MouseX, MouseY);
	}

	return FVector2D(MouseX, MouseY);
}