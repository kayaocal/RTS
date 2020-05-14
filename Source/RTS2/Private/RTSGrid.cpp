// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS2/Public/RTSGrid.h"

RTSGrid::RTSGrid(int ArrayIndex, EGridState NewState)
{
    Index = ArrayIndex;
    GridState = NewState;
}

RTSGrid::~RTSGrid()
{
}
