// Fill out your copyright notice in the Description page of Project Settings.


#include "TestButton.h"
#include "Engine\Engine.h"
#include "RTSUnit.h"
#include "RTS2/Public/RTSActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "Engine/Classes/GameFramework/Pawn.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "RTSGameInstance.h"

void UTestButton::buttonEvent()
{


	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(100,100,15);
	FVector NewDirection = FVector(0, 0, 0);

	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), NewLocation, FRotator::ZeroRotator);

		unit->actor = NewActor;
		NewActor->SetMyUnit(unit);

		URTSGameInstance* GameInstance = RTS_GAME_INSTANCE;

		FUnitDataRow* unitRow = GameInstance->GetUnitConstructionDataRow(TEXT("BaseHouse"));
		
		if (unitRow == nullptr)
		{
			LOG_ERR("UnitRow is null!");
		}
		
		if (unitRow)
		{
			NewActor->ItemStaticMesh->SetStaticMesh(unitRow->StaticMeshData.Construcion1);
			NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)unitRow->StaticMeshData.Material);
		}
		
		PlayerController->SetTemporaryActor(NewActor);
	}


	

	//NewActor->SetMeshFromFile("SM_House_Var01");
	//NewActor->SetTextureFromFile("M_Inst_Pack_04");

	//NewActor->SetActorLocation(NewLocation, false);

	
	
	
	//if (ItemStaticMesh)
	//{
		//ItemStaticMesh->AttachToComponent(NewActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//}

	/*if (GEngine)
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
	}*/
}