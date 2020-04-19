// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "RTSActor.generated.h"


UCLASS()
class RTS2_API ARTSActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSActor();
	void SetMeshFromFile(FString MeshName);
	void SetTextureFromFile(FString MaterialName);
	UStaticMeshComponent* ItemStaticMesh;
	UStaticMesh* CustomMesh;
	UMaterialInstance* CustomMaterial;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
