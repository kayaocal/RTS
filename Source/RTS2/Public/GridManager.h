// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSGrid.h"
#include "RTS2/Game/RTSUnit.h"

/**
 * 
 */
class RTS2_API GridManager
{
public:
	GridManager(FVector2D StartPos,float GridSize,int ColumnCount, int RowCount);
	~GridManager();
	int WorldToGrid(FVector WorldPos);
	FVector GridToWorld(int Index);
	FVector GetGridCenter(int Index);
	FVector GetGridTopMid(int Index);
	FVector GetGridLeftMid(int Index);
	FVector GetGridTopLeft(int Index);
	void SetGridState(int Index, EGridState NewState);
	void SetGridStates(TArray<RTSGrid*> GridsToSet, EGridState NewState);
	TArray<RTSGrid*> GetGridsFromCenter(int Index, int RowCount, int ColumnCount);
	TArray<RTSGrid*> GetNeighbours(int Index, int RowCount, int ColumnCount);
	FVector GetPositionToPlace(int Index, int RowCount, int ColumnCount);
	void PlaceUnit(RTSUnit* UnitToPlace, int Index);
	void RemoveUnit(RTSUnit* UnitToRemove);
	bool IsPlaceable(TArray<RTSGrid*> GridsToPlace, EGridState RequiredState);

	TArray<RTSGrid> RTSGrids;
private:
	FVector2D StartPos;
	int ColumnCount;
	int RowCount;
	int GridSize;
};
