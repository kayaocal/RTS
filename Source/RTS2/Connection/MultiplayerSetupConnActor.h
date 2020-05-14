// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiplayerSetupConnActor.generated.h"

USTRUCT()
struct FRPCData
{
	GENERATED_BODY()
	char* message = "AgeOfVurdurmayanlar";
	int age = 16;
};

UCLASS()
class RTS2_API AMultiplayerSetupConnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplayerSetupConnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void SayHiRPC(FRPCData data);

	UFUNCTION()
	void SayHiRPC_Implementation(FRPCData data);

};
