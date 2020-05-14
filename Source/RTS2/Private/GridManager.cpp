// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS2/Public/GridManager.h"

GridManager::GridManager(FVector2D StartPos, float GridSize, int ColumnCount, int RowCount)
{
    RTSGrids.Reserve(ColumnCount*RowCount);
    for(int i = 0; i < ColumnCount*RowCount; i++)
    {
        RTSGrids.Emplace(i,EGridState::Empty);
    }
    this->StartPos = StartPos;
    this->GridSize = GridSize;
    this->ColumnCount = ColumnCount;
    this->RowCount = RowCount;
}

GridManager::~GridManager()
{
}

int GridManager::WorldToGrid(FVector WorldPos)
{
    int row = (StartPos.X - WorldPos.X)/GridSize;
    int col = (WorldPos.Y - StartPos.Y)/GridSize;
    return row*ColumnCount + col;
}

FVector GridManager::GetGridCenter(int Index)
{
    int row = Index/ColumnCount;
    int col = Index%ColumnCount;

    return FVector(StartPos.X - row*GridSize - GridSize/2, StartPos.Y + col*GridSize + GridSize/2,0);
}

FVector GridManager::GetGridTopMid(int Index)
{
    return  GetGridCenter(Index) + FVector(GridSize/2,0,0);
}

FVector GridManager::GetGridLeftMid(int Index)
{
    return  GetGridCenter(Index) + FVector(0,-GridSize/2,0);
}

FVector GridManager::GetGridTopLeft(int Index)
{
    return GetGridCenter(Index) + FVector(GridSize/2,-GridSize/2,0);
}

void GridManager::SetGridState(int Index, EGridState NewState)
{
    if(RTSGrids.Num() <= 0)
    {
        return;
    }
    RTSGrid GridToSet = RTSGrids[Index];
    GridToSet.GridState = NewState;
}

TArray<RTSGrid*> GridManager::GetGridsFromCenter(int Index, int ARowCount, int AColumnCount)
{
    //todo: add controls for the edges of the map

    
    TArray<RTSGrid*> GridsResult;
    if(Index < 0)
    {
        return GridsResult;  
    }
    GridsResult.Reserve(ARowCount*AColumnCount);

    int RowIndex = Index/this->ColumnCount;
    int ColIndex = Index%this->ColumnCount;
    int ColStart = ColIndex - AColumnCount/2;
    int RowStart = RowIndex - ARowCount/2;
    int StartIndex = RowStart*this->ColumnCount + ColStart;

    for(int i = 0; i < AColumnCount; i++)
    {
        for(int j = 0; j < ARowCount; j++)
        {
            GridsResult.Add(&RTSGrids[StartIndex + (j*this->ColumnCount) +  i]);                
        }
    }
    return GridsResult; 
}

FVector GridManager::GetPositionToPlace(int Index, int ARowCount, int AColumnCount)
{
    if(ARowCount%2 == 0 && AColumnCount %2 == 0)
    {
        return GetGridTopLeft(Index);
    }
    else if(ARowCount%2 == 0)
    {
        return GetGridTopMid(Index);
    }
    else if(AColumnCount %2 == 0)
    {
        return GetGridLeftMid(Index);
    }
    else
    {
        return GetGridCenter(Index);
    }
}

void GridManager::PlaceUnit(RTSUnit* UnitToPlace, int Index)
{
    if(UnitToPlace == nullptr)
    {
        return;
    }
    int RowSize = UnitToPlace->GridRowSize;
    int ColSize = UnitToPlace->GridColSize;
    UnitToPlace->CenterGridIndex = Index;
    SetGridStates( GetGridsFromCenter(Index, RowSize, ColSize), EGridState::Obstacle);
}


void GridManager::RemoveUnit(RTSUnit* UnitToRemove)
{
    if(UnitToRemove == nullptr)
    {
        return;
    }
    int RowSize = UnitToRemove->GridRowSize;
    int ColSize = UnitToRemove->GridColSize;
    SetGridStates( GetGridsFromCenter(UnitToRemove->CenterGridIndex, RowSize, ColSize), EGridState::Empty);
}

bool GridManager::IsPlaceable(TArray<RTSGrid*> GridsToPlace, EGridState RequiredState)
{
    for(int i = 0; i < GridsToPlace.Num(); i++)
    {
        LOG("controlled index %d", GridsToPlace[i]->Index);
        if(GridsToPlace[i] == nullptr || GridsToPlace[i]->GridState != RequiredState)
        {
            LOG("false index %d", GridsToPlace[i]->Index);
            return false;
        }
    }

    return true;
}

void GridManager::SetGridStates(TArray<RTSGrid*> GridsToSet, EGridState NewState)
{
    for(int i = 0; i < GridsToSet.Num(); i++)
    {
        if(GridsToSet[i] == nullptr)
        {
            continue;
        }
        LOG("Grids set to obstacle %d", i);
        LOG("index %d", GridsToSet[i]->Index);
        GridsToSet[i]->GridState = NewState;
    }
}
