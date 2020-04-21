// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/Public/RTSPlayerController.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}
void ARTSPlayerController::Tick(float DeltaSeconds)
{
	if (SelectedActor != nullptr)
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, TraceResult);
		if (TraceResult.GetActor() != nullptr)
		{
			NewLocation = TraceResult.ImpactPoint;
			SelectedActor->SetActorLocation(NewLocation, false);
			if (this->WasInputKeyJustReleased(EKeys::LeftMouseButton))
			{
				SelectedActor = nullptr;
			}
		}
	}
}

void ARTSPlayerController::SetSelectedActor(ARTSActor * NewActor)
{
	SelectedActor = NewActor;
}

