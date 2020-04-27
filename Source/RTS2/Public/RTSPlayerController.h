// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS2/Public/RTSActor.h"
#include "RTS2/RTSUnit.h"
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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds)override;
	class ARTSHud* GetRTSHud();
	class UDebugUIWidget* GetUIWidget();
	void SetUIWidget(class UDebugUIWidget* Widget);
	void SetTemporaryActor(ARTSActor* NewActor);
	void SetSelectedActors(FVector2D StartPos, FVector2D EndPos);
	void SetSelectedActors(ARTSActor* SelectedUnit);
	void ClearSelectedActors();
	ARTSActor* GetSelectedActor(int index);
	

private:
	ARTSActor* TemporaryActor;
	class ARTSHud* RTSHud;
	class UDebugUIWidget* UIWidget;
	TArray<ARTSActor*> SelectedActorsArray;
};
