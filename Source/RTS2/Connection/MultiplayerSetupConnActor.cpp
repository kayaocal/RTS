// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSetupConnActor.h"
#include "RTS2/Prerequisites.h"

// Sets default values
AMultiplayerSetupConnActor::AMultiplayerSetupConnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void AMultiplayerSetupConnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMultiplayerSetupConnActor::SayHiRPC_Implementation(FRPCData data)
{
	LOG_ERR("Server Send Message : %hs ", data.message);
	LOG_ERR("Server Send Message : %d ", data.age);
}



