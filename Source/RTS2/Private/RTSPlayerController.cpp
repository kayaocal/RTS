// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/Public/RTSPlayerController.h"

#include <xkeycheck.h>

#include "RTS2/Public/RTSHud.h"
#include "RTS2/UI/DebugUIWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Engine/Engine.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Game/RTSUnitFactoryComponent.h"
#include "RTS2/Game/RTSManager.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Public/RTSSkeletalActor.h"
#include "RTS2/Public/GridManager.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	PrimaryActorTick.bCanEverTick = true;

	UnitFactory = CreateDefaultSubobject<URTSUnitFactoryComponent>(TEXT("RTSUnitFactory"));
}
void ARTSPlayerController::BeginPlay()
{
	RTSHud = Cast<ARTSHud>(GetHUD());
	TemporaryActor = GetWorld()->SpawnActor<ARTSStaticActor>(ARTSStaticActor::StaticClass(), FVector(0,0, 100), FRotator::ZeroRotator);
	ControllerState = SELECTION;

	TemporaryActor->SetCanAffectNavigationGeneration(false);
	
	if(TemporaryActor->ItemStaticMesh != nullptr)
	{
		TemporaryActor->ItemStaticMesh->SetCanEverAffectNavigation(false);
		
	}
	if(TemporaryActor->SelectionPlaneComponent != nullptr)
	{
		TemporaryActor->SelectionPlaneComponent->SetCanEverAffectNavigation(false);
	}

	TemporaryActor->SetActorEnableCollision(false);
	
	UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	if (NavSystem != nullptr)
	{
		TSet<FNavigationBounds> bounds = NavSystem->GetNavigationBounds();
		FBox Bounds;
		for (auto& Elem : bounds)
		{
			Bounds  = Elem.AreaBox;
			break;
		}
		FVector Center = Bounds.GetCenter();
		FVector Size = Bounds.GetSize();
		FVector Min = Bounds.Min;
		FVector Max = Bounds.Max;
		int GridSize = 100;
		
		GridSystem = new GridManager(FVector2D(Max.X, Min.Y), GridSize, Size.Y/GridSize , Size.X/GridSize);
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("REE222"));
		
	}
}
void ARTSPlayerController::Tick(float DeltaSeconds)
{	
	if (ControllerState == EPlayerControllerState::CONSTRUCTION)
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, TraceResult);
		if (TraceResult.GetActor() != nullptr)
		{
			if(bConstructionRotate)
			{
				FVector2D CurrentMousePos;
				GetMousePosition(CurrentMousePos.X,CurrentMousePos.Y);
				FVector2D MouseDir = CurrentMousePos-ConstructionMousePos;
				if(MouseDir.X == 0)
				{
					return;
				}
				float angle = atan(MouseDir.Y/MouseDir.X);
				angle = FMath::RadiansToDegrees(angle);
				FRotator NewAngle = FRotator(0,angle,0);
				
				TemporaryActor->SetActorRotation(NewAngle);
			}
			else
			{
				if(GridSystem != nullptr)
				{
					//LOG("Grid index = %d", GridSystem->WorldToGrid(TraceResult.ImpactPoint));
					NewLocation = GridSystem->GetPositionToPlace(GridSystem->WorldToGrid(TraceResult.ImpactPoint), ConstructionUnit.GridRowSize, ConstructionUnit.GridColSize);
					ConstructionUnit.CenterGridIndex = GridSystem->WorldToGrid(TraceResult.ImpactPoint);
					TemporaryActor->SetActorLocation(NewLocation, false);

					if(GridSystem->IsPlaceable(GridSystem->GetGridsFromCenter(ConstructionUnit.CenterGridIndex, ConstructionUnit.GridRowSize, ConstructionUnit.GridColSize), EGridState::Empty))
					{
						SetCanConstruct(true);
					}
					else
					{
						SetCanConstruct(false);
					}
				}
				
			}
		}
		return;
	}
}

void ARTSPlayerController::BuildTemporaryUnit()
{
	if(bCanConstruct && TemporaryActor != nullptr)
	{
		RTSUnit* NewUnit =  UnitFactory->CreateUnit(ConstructionUnit.UnitType,  ConstructionUnit.Nation, ConstructionUnit.Color, TemporaryActor->GetActorLocation());
		if(NewUnit != nullptr )
		{
			if(NewUnit->actor!=nullptr)
			{
				NewUnit->actor->SetActorRotation(TemporaryActor->GetActorRotation());
			}
		}
	}
	DisableTemporaryUnit();
}

ARTSHud* ARTSPlayerController::GetRTSHud()
{
	return RTSHud;
}

UDebugUIWidget * ARTSPlayerController::GetUIWidget()
{
	return UIWidget;
}

void ARTSPlayerController::SetUIWidget(UDebugUIWidget * Widget)
{
	UIWidget = Widget;
}

void ARTSPlayerController::SetTemporaryUnit(EUnitTypes UnitType, ENations Nation, EColors Color)
{
	ControllerState = EPlayerControllerState::CONSTRUCTION;
	bCanConstruct = true;

	ConstructionUnit.UnitType = UnitType;
	ConstructionUnit.Nation = Nation;
	ConstructionUnit.Color = Color;

	FUnitDataRow* Row = RTS_DATA.GetUnitConstructionDataRow(UnitNames[UnitType]);
	if(Row == nullptr)
	{
		return;
	}

	ConstructionUnit.GridColSize = Row->GridSizeCol;
	ConstructionUnit.GridRowSize = Row->GridSizeRow;
	
	
	if(Row->IsSkeletalMesh == true)
		return;
	
	RTS_DATA.SetRTSActorSMeshAndMaterial(*TemporaryActor, Nation, UnitType, Color);
	TemporaryActor->SetTextureFromFile("ConstructionMatInstance");
	ShowTemporaryUnit();
}

void ARTSPlayerController::DisableTemporaryUnit()
{
	if(ControllerState != CONSTRUCTION)
	{
		return;
	}

	ControllerState = SELECTION;
	HideTemporaryUnit();
	TemporaryActor->SetActorRotation(FRotator::ZeroRotator);
	SetConstructionRotate(false);
}

void ARTSPlayerController::ShowTemporaryUnit()
{
	TemporaryActor->SetActorHiddenInGame(false);
}

void ARTSPlayerController::HideTemporaryUnit()
{
	TemporaryActor->SetActorHiddenInGame(true);
}

void ARTSPlayerController::SetSelectedActors(FVector2D StartPos, FVector2D EndPos)
{
	ClearSelectedActors();
	if(RTSHud == nullptr)
	{ 
		return;
	}

	if (FVector2D::Distance(StartPos, EndPos) < 20)
	{
		FVector NewLocation = FVector(0, 0, 0);
		FHitResult TraceResult(ForceInit);
		this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TraceResult);

		if (TraceResult.GetActor() != nullptr)
		{	
			ARTSActor* RTSHitActor = Cast<ARTSActor>(TraceResult.GetActor());

			if (RTSHitActor != nullptr)
			{
				SelectedActorsArray.Add(RTSHitActor);
			}
		}
	}
	else
	{
		RTSHud->GetActorsInSelectionRectangle(StartPos, EndPos, SelectedActorsArray, false, false);
	}

	for (int i = 0; i < SelectedActorsArray.Num(); i++)
	{
		if (SelectedActorsArray[i] == nullptr || SelectedActorsArray[i]->GetMyUnit() == nullptr)
		{
			continue;
		}
		SelectedActorsArray[i]->GetMyUnit()->SetSelection(true);
	}

	if (UIWidget != nullptr && SelectedActorsArray.Num() == 1 && SelectedActorsArray[0] != nullptr && SelectedActorsArray[0]->GetMyUnit() != nullptr)
	{
		UIWidget->SetCommandButtonsVisible(SelectedActorsArray[0]->GetMyUnit()->UnitCommands.Num());
	}
}

void ARTSPlayerController::SetSelectedActors(ARTSActor * SelectedActor)
{
	if (SelectedActor == nullptr)
	{
		return;
	}


	ClearSelectedActors();
	SelectedActorsArray.Add(SelectedActor);
	if (SelectedActorsArray[0] == nullptr || SelectedActorsArray[0]->GetMyUnit() == nullptr)
	{
		return;
	}
	SelectedActorsArray[0]->GetMyUnit()->SetSelection(true);
}

void ARTSPlayerController::ClearSelectedActors()
{
	for (int i = 0; i < SelectedActorsArray.Num(); i++)
	{
		if (SelectedActorsArray[i] == nullptr || SelectedActorsArray[i]->GetMyUnit() == nullptr)
		{
			continue;
		}
		SelectedActorsArray[i]->GetMyUnit()->SetSelection(false);
	}
	SelectedActorsArray.Empty();

	if (UIWidget != nullptr)
	{
		UIWidget->SetCommandButtonsVisible(0);
	}
}

ARTSActor * ARTSPlayerController::GetSelectedActor(int index)
{
	if (index < 0 || index >= SelectedActorsArray.Num())
	{
		return nullptr;
	}

	return SelectedActorsArray[index];
}

void ARTSPlayerController::SetConstructionRotate(bool bConstructionRotatePrm)
{
	this->bConstructionRotate = bConstructionRotatePrm;
	if(bConstructionRotatePrm == true)
	{
		GetMousePosition(ConstructionMousePos.X, ConstructionMousePos.Y);
	}
}

EPlayerControllerState ARTSPlayerController::GetControllerState() const
{
	return ControllerState;
}

void ARTSPlayerController::SetCanConstruct(bool bCanConstructPrm)
{
	this->bCanConstruct = bCanConstructPrm;
	if(bCanConstructPrm)
	{
		TemporaryActor->SetTextureFromFile("ConstructionMatInstance");
	}
	else
	{
		TemporaryActor->SetTextureFromFile("ConstructionMatFailInstance");
	}
}

void ARTSPlayerController::MoveUnitsToPosition(FVector_NetQuantize* TargetPos)
{
	for (int i = 0; i < SelectedActorsArray.Num(); ++i)
	{
		if (SelectedActorsArray[i] != nullptr && SelectedActorsArray[i]->GetMyUnit() != nullptr)
		{
			if(SelectedActorsArray[i]->IsSkeletal == true)
			{
				Cast<ARTSSkeletalActor>((SelectedActorsArray[i]))->MoveActor(TargetPos);
			}
		}
	}
}