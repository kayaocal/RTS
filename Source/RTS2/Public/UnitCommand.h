// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RTS2_API UnitCommand
{
public:
	UnitCommand();
	virtual ~UnitCommand();
	virtual void Execute() = 0;
};

class RTS2_API DestroyCommand : public UnitCommand
{
public:
	class RTSUnit* MyUnit = nullptr;
	DestroyCommand(class RTSUnit* Receiver);
	~DestroyCommand();
	void Execute() override;
};
