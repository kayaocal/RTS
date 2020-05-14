// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSetupWidget.h"
#include "RTS2/Public/RTSGameInstance.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "RTS2/GameMode/MultiplayerLobbyGameMode.h"
#include "RTS2/Game/MultiplayerSetupPlayerController.h"
#include "RTS2/Prerequisites.h"

void UMultiplayerSetupWidget::ButtonSendClicked()
{
		URTSGameInstance*  GameInstance = Cast<URTSGameInstance>( UGameplayStatics::GetGameInstance(this));
		AMultiplayerLobbyGameMode* Mode = Cast<AMultiplayerLobbyGameMode>( UGameplayStatics::GetGameMode(this));

		// for(int i = 0; i < Mode->ControllerCount; i++)
		// {
		// 	FRPCData2 data;
		// 	data.age+=i;
		// 	Mode->array[i]->SayHiRPC(data);
		// }

			FRPCData2 data2;
			data2.message = "PofidikAtakan";
			data2.age = 24;
		
			LOG_ERR(" m : %s", *data2.message);
			LOG_ERR(" a : %d", data2.age);
			Mode->array[1]->SayHiRPC(data2);
}
