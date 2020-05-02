// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "RTSActor.generated.h"


UCLASS()
class RTS2_API ARTSActor : public AActor
{
	GENERATED_BODY()

private:
	class RTSUnit* MyUnit;
	int OverlappingUnitsCount = 0;

public:	
	// Sets default values for this actor's properties
	ARTSActor();
	void SetMeshFromFile(FString MeshName);
	void SetTextureFromFile(FString MaterialName);
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* NewComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UStaticMeshComponent* ItemStaticMesh = nullptr;
	UStaticMesh* CustomMesh = nullptr;
	UMaterialInstance* CustomMaterial = nullptr;

	UStaticMeshComponent* SelectionPlaneComponent = nullptr;
	UStaticMesh* SelectionPlaneMesh = nullptr;
	UMaterialInstance* SelectionPlaneMaterial = nullptr;

	UBoxComponent* CollisionBox = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetSelection(bool bIsSelected);
	void SetMyUnit(RTSUnit* AUnit);
	class RTSUnit* GetMyUnit();
};
