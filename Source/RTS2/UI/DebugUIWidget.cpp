// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugUIWidget.h"
#include "RTS2/RTSUnit.h"
#include "RTSGameInstance.h"
#include "RTS2/Prerequisites.h"
#include "RTS2/Data/DataStore.h"
#include "RTS2/Public/RTSActor.h"
#include "RTS2/Data/UnitDataRow.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Types/SlateEnums.h"

#include "RTSGameInstance.h"

void UDebugUIWidget::AssignSpawnUnitCombobox(UComboBoxString * ComboNation, UComboBoxString * ComboUnitType, UComboBoxString * ComboColor)
{

	
	ComboboxNation = ComboNation;
	ComboboxColor = ComboColor;
	ComboboxUnitType = ComboUnitType;

	ComboboxNation->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnNationComboboxChanged);
	ComboboxColor->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnColorComboboxChanged);
	ComboboxUnitType->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnUnitTypeComboboxChanged);
}

void UDebugUIWidget::AssignBankEditableTexts(UEditableText * Wood, UEditableText * Food, UEditableText * Gold)
{
	NBFoodAmountText = Food;
	NBWoodAmountText = Wood;
	NBGoldAmountText = Gold;
	
	if(WidgetNBObserver == nullptr)
	{
		if(RTSGame->GetNationByPlayer(NationIndex))
		{
			RTSGame->GetNationByPlayer(NationIndex)->NationalBank.OnResourceChanged.BindUFunction(this, "OnPlayerResourcesChanged");
		}
	}
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
	NationIndex = 0;
	
	if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0")));}
	if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }

	if (PriceFoodAmountText) { PriceFoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (PriceWoodAmountText) { PriceWoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	if (PriceGoldAmountText) { PriceGoldAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }

	if (ComboboxNation)
	{
		for(int i = 0; i < NATION_COUNT; i++)
		{
			ComboboxNation->AddOption(NationNames[i]);
		}
	}
	ComboboxNation->SetSelectedOption(NationNames[0]);

	if (ComboboxColor)
	{
		for(int i = 0; i < COLOR_COUNT; i++)
		{
			ComboboxColor->AddOption(ColorNames[i]);
		}
	}
	ComboboxColor->SetSelectedOption(ColorNames[0]);

	if (ComboboxUnitType)
	{
		for(int i = 0; i < UNIT_TYPE_COUNT; i++)
		{
			ComboboxUnitType->AddOption(UnitNames[i]);
		}
	}
	ComboboxUnitType->SetSelectedOption(UnitNames[0]);

}

void UDebugUIWidget::GiveResource(int ID, int Amount)
{
	if(RTSGame->GetNationByPlayer(NationIndex) == nullptr)
	{
		return;
	}
	
	switch (ID)
	{
		case 0:
		RTSGame->GetNationByPlayer(NationIndex)->NationalBank.SetFood(RTSGame->GetNationByPlayer(NationIndex)->NationalBank.GetFood() + Amount);
			break;
		case 1:
	    RTSGame->GetNationByPlayer(NationIndex)->NationalBank.SetGold(RTSGame->GetNationByPlayer(NationIndex)->NationalBank.GetGold() + Amount);
			break;
		case 2:
	    RTSGame->GetNationByPlayer(NationIndex)->NationalBank.SetWood(RTSGame->GetNationByPlayer(NationIndex)->NationalBank.GetWood() + Amount);
			break;
		
	}
}

void UDebugUIWidget::OnNationComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo)
{
	SelectedComboboxNation = ComboboxNation->FindOptionIndex(selectedItem);
	UpdateUnitSpawnInfo();
}

void UDebugUIWidget::OnUnitTypeComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo)
{
	SelectedComboboxUnitType = ComboboxUnitType->FindOptionIndex(selectedItem);
	UpdateUnitSpawnInfo();
}

void UDebugUIWidget::OnColorComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo)
{
	SelectedComboboxColor = ComboboxColor->FindOptionIndex(selectedItem);
	UpdateUnitSpawnInfo();
}

void UDebugUIWidget::UpdateUnitSpawnInfo()
{
	if(RTS_GAME_INSTANCE->Game.GetNationByPlayer(NationIndex))
	{
		SelectedUnitPrice = RTS_GAME_INSTANCE->DataStore.GetUnitPrice((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType);
		if(SelectedUnitPrice != nullptr)
		{
			if(PriceFoodAmountText) { PriceFoodAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Food)))); }
			if(PriceGoldAmountText) { PriceGoldAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Gold)))); }
			if(PriceWoodAmountText) { PriceWoodAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Wood)))); }
		}
	}
}

void UDebugUIWidget::OnPlayerResourcesChanged(FRTSPrimitiveResourceData& Resources)
{
	if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString(FString::FromInt(Resources.Food)));}
	if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString(FString::FromInt(Resources.Wood))); }
	if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString(FString::FromInt(Resources.Gold))); }
}

UDebugUIWidget::UDebugUIWidget(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	LOG("CTEST UDebugUIWidget constructor");
	RTSGameInstance = RTS_GAME_INSTANCE;
	RTSGame = &RTS_GAME_INSTANCE->Game;
}

UDebugUIWidget::~UDebugUIWidget()
{

}

void UDebugUIWidget::SpawnUnitButton()
{

	if(SelectedUnitPrice != nullptr)
	{
		if(RTSGame->GetNationByPlayer(NationIndex)->NationalBank.Spend(*SelectedUnitPrice) == false)
		{
			return;
		}
	}
	else
	{
		LOG_ERR("SELECTED UNIT PRICE IS NULL");
		return;
	}
	
	RTSUnit *unit = new RTSUnit();

	FVector NewLocation = FVector(100, 100, 15);
	FVector NewDirection = FVector(0, 0, 0);

	URTSGameInstance* GameInstance = RTS_GAME_INSTANCE;
	DataStore* DataStore = RTS_DATA_STORE;
	FUnitDataRow* unitRow = DataStore->GetUnitConstructionDataRow(UnitNames[SelectedComboboxUnitType]);

	if (unitRow == nullptr)
	{
		LOG_ERR("UnitRow is null!");
		return;
	}
	
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		ARTSActor* NewActor = GetWorld()->SpawnActor<ARTSActor>(ARTSActor::StaticClass(), NewLocation, FRotator::ZeroRotator);

		unit->actor = NewActor;
		NewActor->SetMyUnit(unit);
		if(unitRow->IsSkeletalMesh)
		{
			//NewActor->ItemStaticMesh->SkeletalMesh(RTS_GAME_INSTANCE->DataStore.GetUnitSkeletalMesh((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
			//NewActor->ItemStaticMesh->SetMaterial(RTS_GAME_INSTANCE->DataStore.GetUnitSkeletalMeshMaterial((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
		}
		else
		{
			NewActor->ItemStaticMesh->SetStaticMesh(RTS_GAME_INSTANCE->DataStore.GetUnitStaticMesh((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
			NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)RTS_GAME_INSTANCE->DataStore.GetUnitStaticMeshMaterial((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));		
		}
		

		PlayerController->SetTemporaryActor(NewActor);
	}

}
