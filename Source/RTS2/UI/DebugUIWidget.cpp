// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugUIWidget.h"
#include "RTS2/Game/RTSUnit.h"
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
#include "RTS2/Game/RTSManager.h"
#include "RTS2/Game/RTSUnit.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "UnitCommand.h"
#include "RTS2/Game/RTSUnitFactoryComponent.h"

bool UDebugUIWidget::Initialize()
{
	LOG_ERR("UDebugUIWidget::Initialize()");
	bool Success = Super::Initialize();
	if (!Success) return false;
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		PlayerController->SetUIWidget(this);
	}
	
	CommandButtonArray.Add(Command_1);
	CommandButtonArray.Add(Command_2);
	CommandButtonArray.Add(Command_3);
	CommandButtonArray.Add(Command_4);
	CommandButtonArray.Add(Command_5);
	CommandButtonArray.Add(Command_6);
	CommandButtonArray.Add(Command_7);
	CommandButtonArray.Add(Command_8);
	CommandButtonArray.Add(Command_9);
	CommandButtonArray.Add(Command_10);
	SetCommandButtonsVisible(0);


	if(IS_RTS_NATION_EXIST(NationIndex))
	{
		RTS_NATION(NationIndex)->NationalBank.OnResourceChanged.add<UDebugUIWidget, &UDebugUIWidget::OnPlayerResourcesChanged>(this);
		RTS_NATION(NationIndex)->Population.OnChanged.add<UDebugUIWidget, &UDebugUIWidget::OnPlayerPopulationChanged>(this);
	}	


	return true;
}

void UDebugUIWidget::SetCommandButtonsVisible(int Count)
{
	int i;
	for(i = 0;  i< 10; i++)//todo change 10 to define
	{
		if (CommandButtonArray[i] != nullptr)
		{
			if (i < Count)
			{
				CommandButtonArray[i]->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				CommandButtonArray[i]->SetVisibility(ESlateVisibility::Hidden);
			}
		}	
	}
}


void UDebugUIWidget::AssignSpawnUnitCombobox(UComboBoxString * ComboNation, UComboBoxString * ComboUnitType, UComboBoxString * ComboColor)
{

	ComboboxNation = ComboNation;
	ComboboxColor = ComboColor;
	ComboboxUnitType = ComboUnitType;

	ComboboxNation->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnNationComboboxChanged);
	ComboboxColor->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnColorComboboxChanged);
	ComboboxUnitType->OnSelectionChanged.AddDynamic(this, &UDebugUIWidget::OnUnitTypeComboboxChanged);
}

void UDebugUIWidget::AssignBankEditableTexts(UEditableText * Wood, UEditableText * Food, UEditableText * Gold, UEditableText * Population)
{
	NBFoodAmountText = Food;
	NBWoodAmountText = Wood;
	NBGoldAmountText = Gold;
	PopulationInfoText = Population;
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

	if(IS_RTS_NATION_EXIST(NationIndex))
	{
		if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString((FString::FromInt(RTS_NATION(NationIndex)->NationalBank.GetFood()))));}
		if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString((FString::FromInt(RTS_NATION(NationIndex)->NationalBank.GetWood())))); }
		if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString((FString::FromInt(RTS_NATION(NationIndex)->NationalBank.GetGold())))); }
		if (PopulationInfoText) {PopulationInfoText->SetText(FText::Format(FText::FromString(ANSI_TO_TCHAR("{0}/{1}")),RTS_NATION(NationIndex)->Population.GetPopulation(),RTS_NATION(NationIndex)->Population.GetLimit()));}
	}
	else
	{
		if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0")));}
		if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
		if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString(ANSI_TO_TCHAR("0"))); }
	}

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
	if(IS_RTS_NATION_EXIST(NationIndex) == false)
	{
		return;
	}
	
	switch (ID)
	{
		case 0:
		RTS_NATION(NationIndex)->NationalBank.SetFood(RTS_NATION(NationIndex)->NationalBank.GetFood() + Amount);
			break;
		case 1:
	    RTS_NATION(NationIndex)->NationalBank.SetGold(RTS_NATION(NationIndex)->NationalBank.GetGold() + Amount);
			break;
		case 2:
		default:
	    RTS_NATION(NationIndex)->NationalBank.SetWood(RTS_NATION(NationIndex)->NationalBank.GetWood() + Amount);
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
	if(IS_RTS_NATION_EXIST(NationIndex))
	{
		SelectedUnitPrice = RTS_DATA.GetUnitPrice((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType);
		if(SelectedUnitPrice != nullptr)
		{
			if(PriceFoodAmountText) { PriceFoodAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Food)))); }
			if(PriceGoldAmountText) { PriceGoldAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Gold)))); }
			if(PriceWoodAmountText) { PriceWoodAmountText->SetText(FText::FromString((FString::FromInt(SelectedUnitPrice->Wood)))); }
		}
	}
}

void UDebugUIWidget::OnPlayerPopulationChanged(int Population, int Limit)
{
	LOG("UDebugUIWidget::OnPlayerPopulationChanged");
	if (PopulationInfoText) {PopulationInfoText->SetText(FText::Format(FText::FromString(ANSI_TO_TCHAR("{0}/{1}")),Population,Limit));}
}

void UDebugUIWidget::OnPlayerResourcesChanged(int Wood, int Food, int Gold)
{
	LOG("UDebugUIWidget::OnPlayerResourcesChanged");
	if (NBFoodAmountText) { NBFoodAmountText->SetText(FText::FromString(FString::FromInt(Food)));}
	if (NBWoodAmountText) { NBWoodAmountText->SetText(FText::FromString(FString::FromInt(Wood))); }
	if (NBGoldAmountText) { NBGoldAmountText->SetText(FText::FromString(FString::FromInt(Gold))); }
}

UDebugUIWidget::UDebugUIWidget(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
	
}

UDebugUIWidget::~UDebugUIWidget()
{
	LOG_ERR("Here Destroy");
	if(IS_RTS_NATION_EXIST(NationIndex))
	{
		RTS_NATION(NationIndex)->NationalBank.OnResourceChanged.remove<UDebugUIWidget, &UDebugUIWidget::OnPlayerResourcesChanged>(this);
		RTS_NATION(NationIndex)->Population.OnChanged.remove<UDebugUIWidget, &UDebugUIWidget::OnPlayerPopulationChanged>(this);
	}	
}

void UDebugUIWidget::SpawnUnitButton()
{

	if(SelectedUnitPrice != nullptr)
	{
		if(IS_RTS_NATION_EXIST(NationIndex))
		{
			if(RTS_NATION(NationIndex)->NationalBank.Spend(*SelectedUnitPrice) == false)
			{
				return;
			}
		}
	}
	else
	{
		LOG_ERR("SELECTED UNIT PRICE IS NULL");
		return;
	}


	FVector NewLocation = FVector(100, 100, 15);
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->SetTemporaryUnit((EUnitTypes)SelectedComboboxUnitType, (ENations)SelectedComboboxNation, (EColors)SelectedComboboxColor);
	//URTSUnitFactoryComponent::CreateUnit((EUnitTypes)SelectedComboboxUnitType, NationIndex, NewLocation);
	

}

void UDebugUIWidget::UnitCommandButton(int index)
{
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController != nullptr && PlayerController->GetSelectedActor(0) != nullptr && index >= 0)
	{
		RTSUnit* SelectedUnit = PlayerController->GetSelectedActor(0)->GetMyUnit();
		if (SelectedUnit != nullptr && SelectedUnit->UnitCommands[index] != nullptr)
		{
			SelectedUnit->UnitCommands[index]->Execute();
		}
	}
}
