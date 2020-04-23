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

void ARTSPlayerController::SetTemporaryActor(ARTSActor * NewActor)
{
	TemporaryActor = NewActor;
}

