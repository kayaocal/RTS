// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"

#include "Components/MenuAnchor.h"
#include "RTS2/Template/ObserverTemplate.h"
#include "RTS2/Data/RTSPrimitiveResourceData.h"

#include "DebugUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UDebugUIWidget : public UUserWidget
{
	
	GENERATED_BODY()

	int NationIndex;
	UComboBoxString* ComboboxNation;
	UComboBoxString* ComboboxUnitType;
	UComboBoxString* ComboboxColor;

	//NB = NationalBank
	UEditableText*	NBFoodAmountText;
	UEditableText*	NBGoldAmountText;
	UEditableText*	NBWoodAmountText;

	UEditableText*	PriceFoodAmountText;
	UEditableText*	PriceGoldAmountText;
	UEditableText*	PriceWoodAmountText;

	UMenuAnchor*	CreateUnitMenuAnchor;

	int SelectedComboboxNation;
	int SelectedComboboxColor;
	int SelectedComboboxUnitType;
	FRTSPrimitiveResourceData* SelectedUnitPrice;
	
	class WidgetPrimitiveResObserver* WidgetNBObserver;

	UDebugUIWidget(const FObjectInitializer& ObjectInitializer);
	~UDebugUIWidget();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void SpawnUnitButton();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void UnitCommandButton(int index);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void AssignSpawnUnitCombobox(UComboBoxString* ComboNation, UComboBoxString* ComboUnitType, UComboBoxString* ComboColor);
		
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void AssignBankEditableTexts(UEditableText* Wood, UEditableText* Food, UEditableText* Gold);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void AssignPriceEditableTexts(UEditableText* Wood, UEditableText* Food, UEditableText* Gold);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void AssignCreateUnitMenuAnchor(UMenuAnchor* Menu);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void SetMenuDefaults();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GiveResource(int ID, int Amount);
	
	public:
		
	UPROPERTY(meta = (BindWidget))
	class UButton* Command_1 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_2 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_3 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_4 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_5 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_6 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_7 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_8 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_9 = nullptr;

	UPROPERTY(meta = (BindWidget))
	class UButton* Command_10 = nullptr;

	TArray<UButton*> CommandButtonArray;

	void UpdateBank(RTSPrimitiveResources& Source);
	
	virtual bool Initialize() override;
	
	void SetCommandButtonsVisible(int Count);
	
	UFUNCTION(BlueprintCallable)
	void OnNationComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo);

	UFUNCTION(BlueprintCallable)
	void OnUnitTypeComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo);

	UFUNCTION(BlueprintCallable)
	void OnColorComboboxChanged(FString selectedItem, ESelectInfo::Type selectInfo);
	
	void UpdateUnitSpawnInfo();


public:

	UFUNCTION()
	void OnPlayerResourcesChanged(FRTSPrimitiveResourceData& Resources);

};

	
