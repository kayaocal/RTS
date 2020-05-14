// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
//#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "RTSActor.generated.h"


UCLASS()
class RTS2_API ARTSActor : public APawn
{
	GENERATED_BODY()

protected:
	class RTSUnit* MyUnit;

public:	
	// Sets default values for this actor's properties
	ARTSActor();
	void SetMeshFromFile(FString MeshName);
	void SetTextureFromFile(FString MaterialName);
	//UStaticMeshComponent* ItemStaticMesh = nullptr;
	//USkeletalMeshComponent* ItemSkeletalMesh = nullptr;
	UStaticMesh* CustomMesh = nullptr;
	UMaterialInstance* CustomMaterial = nullptr;

	UStaticMeshComponent* SelectionPlaneComponent = nullptr;
	UStaticMesh* SelectionPlaneMesh = nullptr;
	UMaterialInstance* SelectionPlaneMaterial = nullptr;
	bool IsSkeletal = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetSelection(bool bIsSelected);
	void SetMyUnit(RTSUnit* AUnit);
	class RTSUnit* GetMyUnit();
	void SetGridScale(int RowSize, int ColSize);
};
