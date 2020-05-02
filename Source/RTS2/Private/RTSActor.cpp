// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSActor.h"
#include "Engine.h"
#include "RTS2/Data/UnitDataRow.h"
#include "RTS2/Public/RTSPlayerController.h"
#include "RTS2/Prerequisites.h"



#include "Kismet/GameplayStatics.h"
#include "RTSGameInstance.h"

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
	SelectionPlaneComponent->SetVisibility(false);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	CollisionBox->AttachToComponent(ItemStaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	CollisionBox->SetWorldScale3D(FVector(9,9,9));
	CollisionBox->SetGenerateOverlapEvents(false);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,  &ARTSActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this,  &ARTSActor::OnOverlapEnd);
	
	FString PathString = TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	const TCHAR*  PathChars = *PathString;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(PathChars);

	if (MeshAsset.Succeeded())
	{
		SelectionPlaneComponent->SetStaticMesh(MeshAsset.Object);
		SelectionPlaneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
		SelectionPlaneComponent->SetWorldScale3D(FVector(9.f, 9.f, 0.1f));
	}

	PathString = TEXT("MaterialInstanceConstant'/Game/Materials/SelectionCircleMatInstance.SelectionCircleMatInstance'");
	PathChars = *PathString;

	ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialAsset(PathChars);
	if (MaterialAsset.Succeeded())
	{
		SelectionPlaneComponent->SetMaterial(0,MaterialAsset.Object);
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
	FString PathString = TEXT("MaterialInstanceConstant'/Game/Materials/");

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
		
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("texture not found"));
		}
	}

}

void ARTSActor::OnOverlapBegin(class UPrimitiveComponent* NewComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(this == OtherActor || OtherActor == nullptr || OtherComp == nullptr)
	{
		return;
	}
	
	ARTSActor* CollidingActor = Cast<ARTSActor>(OtherActor);
	if(CollidingActor == nullptr)
	{
		return;
	}
	
	this->SetTextureFromFile("ConstructionMatFailInstance");
	ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr)
	{
		PlayerController->SetCanConstruct(false);
	}
	OverlappingUnitsCount++;

}

void ARTSActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(this == OtherActor || OtherActor == nullptr || OtherComp == nullptr)
	{
		return;
	}
	ARTSActor* CollidingActor = Cast<ARTSActor>(OtherActor);
	if(CollidingActor == nullptr)
	{
		return;
	}
	OverlappingUnitsCount--;
	if(OverlappingUnitsCount <= 0)
	{
		this->SetTextureFromFile("ConstructionMatInstance");
		ARTSPlayerController* PlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerController != nullptr)
		{
			PlayerController->SetCanConstruct(true);
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

void ARTSActor::SetSelection(bool bIsSelected)
{
	if (SelectionPlaneComponent == nullptr)
	{
		return;
	}

	SelectionPlaneComponent->SetVisibility(bIsSelected);
}

void ARTSActor::SetMyUnit(RTSUnit * AUnit)
{
	MyUnit = AUnit;
}

RTSUnit * ARTSActor::GetMyUnit()
{
	return MyUnit;
}

