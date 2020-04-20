// Fill out your copyright notice in the Description page of Project Settings.


#include "AiNavigationController.h"
#include "Engine.h"

void AAiNavigationController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	GoToRandomWaypoint();
}

ATargetPoint* AAiNavigationController::GetRandomWaypoint()
{
	auto index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

void AAiNavigationController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint());
}

void AAiNavigationController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAiNavigationController::GoToRandomWaypoint, 0.2f, false);
}

