// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"

#include "Components/MenuAnchor.h"
#include "RTS2/Template/ObserverTemplate.h"

#include "DebugUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UDebugUIWidget : public UUserWidget
{
	
	GENERATED_BODY()

	int NationIndex;
	class URTSGameInstance* RTSGameInstance;
	class RTSGame* RTSGame;
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

	class WidgetPrimitiveResObserver* WidgetNBObserver;

	UDebugUIWidget(const FObjectInitializer& ObjectInitializer);
	~UDebugUIWidget();
	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void SpawnUnitButton();

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
	void UpdateBank(RTSPrimitiveResources& Source);
};

class RTS2_API WidgetPrimitiveResObserver
	: public Observer<RTSPrimitiveResources>
{
	UDebugUIWidget* Widget;
	RTSNation* Nation;
	
	public:

	WidgetPrimitiveResObserver(UDebugUIWidget* widget, RTSNation*  Nation);
	~WidgetPrimitiveResObserver();
	void OnFieldChanged(RTSPrimitiveResources& Source) override;
};
