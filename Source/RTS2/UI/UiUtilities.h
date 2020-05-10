#pragma once
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
};


