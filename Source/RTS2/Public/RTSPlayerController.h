// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Public/RTSActor.h"
#include "RTS2/Game/RTSUnit.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */

enum EPlayerControllerState
{
	NONE,
	SELECTION,
	CONSTRUCTION
};

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
	void SetTemporaryUnit(EUnitTypes UnitType, ENations Nation, EColors Color);
	void DisableTemporaryUnit();
	void ShowTemporaryUnit();
	void HideTemporaryUnit();
	void SetSelectedActors(FVector2D StartPos, FVector2D EndPos);
	void SetSelectedActors(ARTSActor* SelectedUnit);
	void ClearSelectedActors();
	ARTSActor* GetSelectedActor(int index);

	class URTSUnitFactoryComponent* UnitFactory;

private:
	ARTSActor* TemporaryActor;
	class ARTSHud* RTSHud;
	class UDebugUIWidget* UIWidget;
	TArray<ARTSActor*> SelectedActorsArray;

	EPlayerControllerState ControllerState;


	EUnitTypes		ConstructUnitType;
	ENations		ConstructNation;
	EColors			ConstructColor;
	
	
};
