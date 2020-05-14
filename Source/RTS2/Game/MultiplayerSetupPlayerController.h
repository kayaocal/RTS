// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerSetupPlayerController.generated.h"

USTRUCT()
struct FRPCData2
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString message = "VurduranAtakan";
	UPROPERTY()
	int age;

};

/**
 * 
 */
UCLASS()
class RTS2_API AMultiplayerSetupPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	
	UFUNCTION(Client, Reliable, WithValidation)
	void SayHiRPC(const FRPCData2& data);

	UFUNCTION()
	void SayHiRPC_Implementation(const FRPCData2& data);

	UFUNCTION()
	bool SayHiRPC_Validate(const FRPCData2& data);

	UFUNCTION(Server, Reliable)
	void LetsPlay();

	UFUNCTION()
	void LetsPlay_Implementation();
};
