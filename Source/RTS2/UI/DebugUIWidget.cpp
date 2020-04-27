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
#include "RTS2/Game/RTSManager.h"
#include "RTSGameInstance.h"
#include "RTS2/RTSUnit.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "UnitCommand.h"

bool UDebugUIWidget::Initialize()
{
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

void UDebugUIWidget::AssignBankEditableTexts(UEditableText * Wood, UEditableText * Food, UEditableText * Gold)
{
	NBFoodAmountText = Food;
	NBWoodAmountText = Wood;
	NBGoldAmountText = Gold;
	
	if(WidgetNBObserver == nullptr)
	{
		if(RTS_NATION(NationIndex))
		{
			//TODO Delegate Unbind yapmali mi ogren!!!
			RTS_NATION(NationIndex)->NationalBank.OnResourceChanged.BindUFunction(this, "OnPlayerResourcesChanged");
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
	if(RTS_NATION(NationIndex) == nullptr)
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
	if(RTS_NATION(NationIndex))
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
}

UDebugUIWidget::~UDebugUIWidget()
{
	if(RTS_NATION(NationIndex))
	{
		if(RTS_NATION(NationIndex)->NationalBank.OnResourceChanged.IsBound())
		{
			//RTS_NATION(NationIndex)->NationalBank.OnResourceChanged.Unbind(this, "OnPlayerResourcesChanged");
		}
	}
}

void UDebugUIWidget::SpawnUnitButton()
{

	if(SelectedUnitPrice != nullptr)
	{
		if(RTS_NATION(NationIndex)->NationalBank.Spend(*SelectedUnitPrice) == false)
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

	FUnitDataRow* unitRow = RTS_DATA.GetUnitConstructionDataRow(UnitNames[SelectedComboboxUnitType]);

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
			NewActor->ItemStaticMesh->SetStaticMesh(RTS_DATA.GetUnitStaticMesh((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));
			NewActor->ItemStaticMesh->SetMaterial(0, (UMaterialInterface*)RTS_DATA.GetUnitStaticMeshMaterial((ENations)SelectedComboboxNation, (EUnitTypes)SelectedComboboxUnitType));		
		}

		PlayerController->SetTemporaryActor(NewActor);
	}

	DestroyCommand* NewCommand = new DestroyCommand(unit);

	unit->UnitCommands.Add(NewCommand);

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
