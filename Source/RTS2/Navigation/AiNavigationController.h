// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AiNavigationController.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API AAiNavigationController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
private:
	UPROPERTY()
		TArray<AActor*> Waypoints;

	UFUNCTION()
		ATargetPoint* GetRandomWaypoint();

	UFUNCTION()
		void GoToRandomWaypoint();

	FTimerHandle TimerHandle;
	
};
