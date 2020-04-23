// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Public/RTSHud.h"
#include "Engine/Engine.h"

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

	if (this->WasInputKeyJustReleased(EKeys::LeftMouseButton))
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, TraceResult);
	}
}

ARTSHud* ARTSPlayerController::GetRTSHud()
{
	return RTSHud;
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
	RTSHud->GetActorsInSelectionRectangle(StartPos, EndPos, SelectedActorsArray, false, false);

	for (int i = 0; i < SelectedActorsArray.Num(); i++)
	{
		if (SelectedActorsArray[i] == nullptr || SelectedActorsArray[i]->GetMyUnit() == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("dongu"));
			continue;
		}
		SelectedActorsArray[i]->GetMyUnit()->SetSelection(true);
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
}