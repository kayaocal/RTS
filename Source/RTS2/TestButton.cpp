// Fill out your copyright notice in the Description page of Project Settings.


#include "TestButton.h"
#include "Engine\Engine.h"
#include "RTSUnit.h"
#include "RTS2/Public/RTSActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Prerequisites.h"

void UTestButton::buttonEvent()
{
	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(100,100,15);
	ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), NewLocation, FRotator::ZeroRotator);

	unit->actor = NewActor;

	FSoftObjectPath UnitDataTablePath = FSoftObjectPath(TEXT("DataTable'/Game/Data/UnitConstructionData.UnitConstructionData'"));

	FUnitDataRow* unitRow = nullptr;
	UDataTable* UnitConstructionData = nullptr;

	UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.ResolveObject());

	if (UnitConstructionData == nullptr)
	{
		UnitConstructionData = Cast<UDataTable>(UnitDataTablePath.TryLoad());
	}

	if (UnitConstructionData != nullptr)
	{
		unitRow = UnitConstructionData->FindRow<FUnitDataRow>(FName(TEXT("BaseHouse2")), TEXT(""));
	}

	//NewActor->SetMeshFromFile("SM_House_Var01");
	//NewActor->SetTextureFromFile("M_Inst_Pack_04");

	NewActor->SetActorLocation(NewLocation, false);

	if (unitRow)
	{
		NewActor->ItemStaticMesh->SetStaticMesh(unitRow->StaticMeshData.Construcion1);
		NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)unitRow->StaticMeshData.Material);
	}
	
	
	//if (ItemStaticMesh)
	//{
		//ItemStaticMesh->AttachToComponent(NewActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Unit Created"));
		if (unitRow)
		{
			if (unitRow->IsSkeletalMesh)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Skeletal"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Skeletal degil "));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("unitRow is null"));
		}
	}
}