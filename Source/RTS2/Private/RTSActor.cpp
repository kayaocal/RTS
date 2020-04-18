// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARTSActor::ARTSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* ItemStaticMesh = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	ItemStaticMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ARTSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTSActor::AddStaticMesh()
{
	
	//UCapsuleComponent* ItemStaticMesh = CreateDefaultSubobject<UCapsuleComponent>( TEXT("Capsule"));
	//ItemStaticMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}

