// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS2/Public/RTSActor.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSPlayerController();
	virtual void Tick(float DeltaSeconds)override;
	void SetTemporaryActor(ARTSActor* NewActor);
private:
	ARTSActor* TemporaryActor;
	TArray<ARTSActor*> SelectedActorsArray;
};
