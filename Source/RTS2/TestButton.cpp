// Fill out your copyright notice in the Description page of Project Settings.


#include "TestButton.h"
#include "Engine\Engine.h"
#include "RTSUnit.h"
#include "RTS2/Public/RTSActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UTestButton::buttonEvent()
{
	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(0.f, 0.f, 0.f);
	ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), NewLocation, FRotator::ZeroRotator);

	unit->actor = NewActor;
	
	NewActor->AddStaticMesh();
	
	
	//if (ItemStaticMesh)
	//{
		//ItemStaticMesh->AttachToComponent(NewActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Unit Created"));
	}
}