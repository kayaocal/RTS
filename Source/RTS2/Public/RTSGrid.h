// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

enum EGridState
{
	Empty = 0,
	Obstacle = 1
};

class RTS2_API RTSGrid
{
public:
	RTSGrid(int ArrayIndex, EGridState NewState);
	~RTSGrid();
	int Index;
	EGridState GridState = EGridState::Empty;
};
