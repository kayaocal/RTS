#pragma once
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"
#include "Components/Widget.h"

class UiUtilities {
public:

	static void SafeSetVisibility(UWidget* Widget, const ESlateVisibility Visibility)
	{
		if(Widget)
		{
			Widget->SetVisibility(Visibility);
		}
	}

	static void SafeSetIsEnabled(UWidget* Widget, const bool IsEnabled)
	{
		if(Widget)
		{
			Widget->SetIsEnabled(IsEnabled);
		}
	}

	static void SafeSetEditableText(UEditableText* EText, FText InText)
	{
		if(EText)
		{
			EText->SetText(InText);
		}
	}
	
	static void SafeFillComboboxWNation(UComboBoxString* Combo, int SelectedOption = 0)
	{
		if(Combo)
		{
			for(int i = 0; i < NATION_COUNT; i++)
			{
				Combo->AddOption(NationNames[i]);
			}

			Combo->SetSelectedOption(NationNames[SelectedOption]);
		}
	}

	static void SafeFillComboboxWColor(UComboBoxString* Combo, int SelectedOption = 0)
	{
		if(Combo)
		{
			for(int i = 0; i < COLOR_COUNT; i++)
			{
				Combo->AddOption(ColorNames[i]);
			}

			Combo->SetSelectedOption(ColorNames[SelectedOption]);
		}
	}

	static void SafeFillComboboxWUnits(UComboBoxString* Combo, int SelectedOption = 0)
	{
		if (Combo)
		{
			for(int i = 0; i < UNIT_TYPE_COUNT; i++)
			{
				Combo->AddOption(UnitNames[i]);
			}
			Combo->SetSelectedOption(UnitNames[0]);
		}
	}
};


