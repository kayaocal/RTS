// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/RTSUnit.h"
#include "DebugUIWidget.h"
#include "RTSGameInstance.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Data/DataStore.h"
#include "RTS2/Public/RTSActor.h"
#include "RTS2/Data/UnitDataRow.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "Engine/Classes/GameFramework/Pawn.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

void UDebugUIWidget::AssignSpawnUnitCombobox(UComboBoxString * ComboNation, UComboBoxString * ComboUnitType, UComboBoxString * ComboColor)
{
	ComboboxNation = ComboNation;
	ComboboxColor = ComboColor;
	ComboboxUnitType = ComboUnitType;
}

void UDebugUIWidget::AssignBankEditableTexts(UEditableText * Wood, UEditableText * Food, UEditableText * Gold)
{
	NBFoodAmountText = Food;
	NBWoodAmountText = Wood;
	NBGoldAmountText = Gold;
}

void UDebugUIWidget::AssignPriceEditableTexts(UEditableText * Wood, UEditableText * Food, UEditableText * Gold)
{
	PriceFoodAmountText = Food;
	PriceWoodAmountText = Wood;
	PriceGoldAmountText = Gold;
}

void UDebugUIWidget::AssignCreateUnitMenuAnchor(UMenuAnchor * Menu)
{
	CreateUnitMenuAnchor = Menu;
}

void UDebugUIWidget::SetMenuDefaults()
{
	if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0")));}
	if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }

	if (PriceFoodAmountText) { PriceFoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (PriceWoodAmountText) { PriceWoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (PriceGoldAmountText) { PriceGoldAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }

	if (ComboboxNation)
	{
		ComboboxNation->AddOption("NATION 1");
		ComboboxNation->AddOption("NATION 2");
		ComboboxNation->AddOption("NATION 3");
	}

	if (ComboboxColor)
	{
		ComboboxColor->AddOption("RED");
		ComboboxColor->AddOption("GREEN");
		ComboboxColor->AddOption("BLUE");
		ComboboxColor->AddOption("YELLOW");
	}

	if (ComboboxUnitType)
	{
		ComboboxUnitType->AddOption("BASE BUILDING");
		ComboboxUnitType->AddOption("HOUSE");
		ComboboxUnitType->AddOption("ARCHERY");
	}

}

void UDebugUIWidget::SpawnUnitButton()
{

	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(100, 100, 15);
	FVector NewDirection = FVector(0, 0, 0);

	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), NewLocation, FRotator::ZeroRotator);

		unit->actor = NewActor;
		NewActor->SetMyUnit(unit);

		URTSGameInstance* GameInstance = RTS_GAME_INSTANCE;
		DataStore* DataStore = RTS_DATA_STORE;
		FUnitDataRow* unitRow = DataStore->GetUnitConstructionDataRow(TEXT("BaseHouse"));

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

}