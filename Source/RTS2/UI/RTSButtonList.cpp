// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSButtonList.h"


URTSButtonList::URTSButtonList()
	:UButton()
{
	
}

URTSButtonList::~URTSButtonList()
{
	OnClicked.RemoveAll(this);
}


void URTSButtonList::SetButtonIndex(int Index)
{
	ButtonIndex = Index;
	OnClicked.AddDynamic(this, &URTSButtonList::ButtonClickEvent);
}

void URTSButtonList::ButtonClickEvent()
{
	LOG_W("ButtonClickEvent");
	OnRTSButtonListClicked(ButtonIndex);
}
