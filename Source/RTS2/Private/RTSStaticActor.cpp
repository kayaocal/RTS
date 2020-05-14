#include "RTS2/Public/RTSStaticActor.h"

ARTSStaticActor::ARTSStaticActor()
{
	FString fstringVar = "ARTSStaticActor  CONSTRL START";
    UE_LOG(LogTemp, Warning, TEXT("Text,  %s"), *fstringVar );
    ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	ItemStaticMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	ItemStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	SelectionPlaneComponent->AttachToComponent(ItemStaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	fstringVar = "ARTSStaticActor  CONSTRL END";
	UE_LOG(LogTemp, Warning, TEXT("Text,  %s"), *fstringVar );

}
