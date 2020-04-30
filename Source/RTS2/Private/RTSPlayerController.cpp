// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Public/RTSHud.h"
#include "RTS2/UI/DebugUIWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Engine/Engine.h"
#include "RTS2/Prerequisites.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}
void ARTSPlayerController::BeginPlay()
{
	RTSHud = Cast<ARTSHud>(GetHUD());
}
void ARTSPlayerController::Tick(float DeltaSeconds)
{
	if (TemporaryActor != nullptr)
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, TraceResult);
		if (TraceResult.GetActor() != nullptr)
		{
			NewLocation = TraceResult.ImpactPoint;
			TemporaryActor->SetActorLocation(NewLocation, false);
			if (this->WasInputKeyJustReleased(EKeys::LeftMouseButton))
			{
				TemporaryActor = nullptr;
				return;
			}
		}
		return;
	}
}

ARTSHud* ARTSPlayerController::GetRTSHud()
{
	return RTSHud;
}

UDebugUIWidget * ARTSPlayerController::GetUIWidget()
{
	return UIWidget;
}

void ARTSPlayerController::SetUIWidget(UDebugUIWidget * Widget)
{
	UIWidget = Widget;
}

void ARTSPlayerController::SetTemporaryActor(ARTSActor * NewActor)
{
	TemporaryActor = NewActor;
}

void ARTSPlayerController::SetSelectedActors(FVector2D StartPos, FVector2D EndPos)
{
	ClearSelectedActors();
	if(RTSHud == nullptr)
	{ 
		return;
	}

	if (FVector2D::Distance(StartPos, EndPos) < 20)
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

		if (TraceResult.GetActor() != nullptr)
		{
			ARTSActor* RTSHitActor = Cast<ARTSActor>(TraceResult.GetActor());

			if (RTSHitActor != nullptr)
			{
				SelectedActorsArray.Add(RTSHitActor);
			}
		}
	}
	else
	{
		RTSHud->GetActorsInSelectionRectangle(StartPos, EndPos, SelectedActorsArray, false, false);
	}

	for (int i = 0; i < SelectedActorsArray.Num(); i++)
	{
		if (SelectedActorsArray[i] == nullptr || SelectedActorsArray[i]->GetMyUnit() == nullptr)
		{
			continue;
		}
		SelectedActorsArray[i]->GetMyUnit()->SetSelection(true);
	}

	if (UIWidget != nullptr && SelectedActorsArray.Num() == 1 && SelectedActorsArray[0] != nullptr && SelectedActorsArray[0]->GetMyUnit() != nullptr)
	{
		UIWidget->SetCommandButtonsVisible(SelectedActorsArray[0]->GetMyUnit()->UnitCommands.Num());
	}
}

void ARTSPlayerController::SetSelectedActors(ARTSActor * SelectedActor)
{
	if (SelectedActor == nullptr)
	{
		return;
	}


	ClearSelectedActors();
	SelectedActorsArray.Add(SelectedActor);
	if (SelectedActorsArray[0] == nullptr || SelectedActorsArray[0]->GetMyUnit() == nullptr)
	{
		return;
	}
	SelectedActorsArray[0]->GetMyUnit()->SetSelection(true);
}

void ARTSPlayerController::ClearSelectedActors()
{
	for (int i = 0; i < SelectedActorsArray.Num(); i++)
	{
		if (SelectedActorsArray[i] == nullptr || SelectedActorsArray[i]->GetMyUnit() == nullptr)
		{
			continue;
		}
		SelectedActorsArray[i]->GetMyUnit()->SetSelection(false);
	}
	SelectedActorsArray.Empty();

	if (UIWidget != nullptr)
	{
		UIWidget->SetCommandButtonsVisible(0);
	}
}

ARTSActor * ARTSPlayerController::GetSelectedActor(int index)
{
	if (index < 0 || index >= SelectedActorsArray.Num())
	{
		return nullptr;
	}

	return SelectedActorsArray[index];
}
