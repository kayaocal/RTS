// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSActor.h"
#include "Engine.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Prerequisites.h"

// Sets default values
ARTSActor::ARTSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	ItemStaticMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	ItemStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	SelectionPlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("SelectionPlane"));
	SelectionPlaneComponent->AttachToComponent(ItemStaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SelectionPlaneComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	
	FString PathString = TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	const TCHAR*  PathChars = *PathString;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(PathChars);

	if (MeshAsset.Succeeded())
	{
		SelectionPlaneComponent->SetStaticMesh(MeshAsset.Object);
		SelectionPlaneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
		SelectionPlaneComponent->SetWorldScale3D(FVector(9.f, 9.f, 0));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh Added"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh not found"));
		}
	}

	PathString = TEXT("MaterialInstanceConstant'/Game/Materials/SelectionCircleMatInstance.SelectionCircleMatInstance'");
	PathChars = *PathString;

	ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialAsset(PathChars);
	if (MaterialAsset.Succeeded())
	{
		SelectionPlaneComponent->SetMaterial(0,MaterialAsset.Object);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Material Added"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Material not found"));
		}
	}
	
}

void ARTSActor::SetMeshFromFile(FString MeshName)
{
	FString PathString = TEXT("StaticMesh'/Game/AdvancedVillagePack/Meshes/");

	PathString += MeshName + "." + MeshName + "'";


	FSoftObjectPath MeshPath = FSoftObjectPath(PathString);

	/*const TCHAR*  PathChars = *PathString;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(PathChars);

	if (MeshAsset.Succeeded())
	{
		ItemStaticMesh->SetStaticMesh(MeshAsset.Object);
		ItemStaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ItemStaticMesh->SetWorldScale3D(FVector(1.f));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh Added"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh not found"));
		}
	}*/

	CustomMesh = Cast<UStaticMesh>(MeshPath.ResolveObject());
	if (CustomMesh == nullptr)
	{
		CustomMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
	}

	if (CustomMesh != nullptr)
	{
		ItemStaticMesh->SetStaticMesh(CustomMesh);
		ItemStaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ItemStaticMesh->SetWorldScale3D(FVector(1.f));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh Added"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mesh not found"));
		}
	}

}

void ARTSActor::SetTextureFromFile(FString MaterialName)
{
	FString PathString = TEXT("MaterialInstanceConstant'/Game/AdvancedVillagePack/Materials/");

	PathString += MaterialName + "." + MaterialName + "'";


	FSoftObjectPath TexturePath = FSoftObjectPath(PathString);

	CustomMaterial = Cast<UMaterialInstance>(TexturePath.ResolveObject());
	if (CustomMaterial == nullptr)
	{
		CustomMaterial = Cast<UMaterialInstance>(TexturePath.TryLoad());
	}

	if (CustomMaterial != nullptr)
	{
		ItemStaticMesh->SetMaterial(0,CustomMaterial);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("texture added"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("texture not found"));
		}
	}

}

// Called when the game starts or when spawned
void ARTSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

