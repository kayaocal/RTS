// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS2/Public/RTSPlayerCameraSpectatorPawn.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/Engine/Engine.h"

ARTSPlayerCameraSpectatorPawn::ARTSPlayerCameraSpectatorPawn(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bAddDefaultMovementBindings = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bCanMoveCamera = true;

	// collision
	GetCollisionComponent()->SetGenerateOverlapEvents(false);
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCollisionComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCollisionComponent()->SetSimulatePhysics(false);

	CameraXYLimit = 7500.f;
	CameraHeight = 4000.f;
	CameraHeightMin = 1500.f;
	CameraHeightMax = 5000.f;

	CameraRadius = 1100.f;
	CameraRadiusMin = 500.f;
	CameraRadiusMax = 8000.f;

	CameraZAngle = 0.f;
	CameraHeightAngle = 50.f;                // pitch
	CameraHeightAngleMin = 15.f;
	CameraHeightAngleMax = 85.f;


	CameraZoomSpeed = 200.f;
	CameraMovementSpeed = 3000.f;
	CameraRotationSpeed = 10.f;

	CameraScrollBoundary = 30.f; // screen edge margin

	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("RTS Camera"));
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->bUsePawnControlRotation = false;
	RepositionCamera();
}

void ARTSPlayerCameraSpectatorPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		return;
	}

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ZoomOutByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::ZoomOutByWheel);
	PlayerInputComponent->BindAction("ZoomInByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::ZoomInByWheel);
	PlayerInputComponent->BindAction("RotateUpByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateUpByWheel);
	PlayerInputComponent->BindAction("RotateDownByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateDownByWheel);
	PlayerInputComponent->BindAction("RotateLeftByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateLeftByWheel);
	PlayerInputComponent->BindAction("RotateRightByWheel", IE_Pressed, this, &ARTSPlayerCameraSpectatorPawn::RotateRightByWheel);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraForwardInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraRightInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ARTSPlayerCameraSpectatorPawn::MoveCameraUpInput);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ARTSPlayerCameraSpectatorPawn::ZoomCameraInInput);
	PlayerInputComponent->BindAxis("Rotate", this, &ARTSPlayerCameraSpectatorPawn::RotateInput);

}

void ARTSPlayerCameraSpectatorPawn::RotateInput(float Direction)
{
	if (!bCanMoveCamera)
	{
		return;
	}

	RotateValue = FMath::Abs(Direction);
}

void ARTSPlayerCameraSpectatorPawn::ZoomInByWheel()
{
	if (!bCanMoveCamera) 
	{
		return;
	}

	CameraRadius -= CameraZoomSpeed;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

}

void ARTSPlayerCameraSpectatorPawn::ZoomOutByWheel()
{
	if (!bCanMoveCamera)
	{
		return;
	}

	CameraRadius += CameraZoomSpeed;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);
}

void ARTSPlayerCameraSpectatorPawn::RotateLeftByWheel()
{
	if (!bCanMoveCamera)
	{
		return;
	}

	CameraZAngle -= CameraRotationSpeed;
}

void ARTSPlayerCameraSpectatorPawn::RotateRightByWheel()
{
	if (!bCanMoveCamera)
	{
		return;
	}

	CameraZAngle += CameraRotationSpeed;
}

void ARTSPlayerCameraSpectatorPawn::RotateUpByWheel()
{
	if (!bCanMoveCamera)
	{
		return;
	}

	CameraHeightAngle += CameraRotationSpeed;
	CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);
}

void ARTSPlayerCameraSpectatorPawn::RotateDownByWheel()
{
	if (!bCanMoveCamera)
	{
		return;
	}

    CameraHeightAngle -= CameraRotationSpeed;
    CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

}

void ARTSPlayerCameraSpectatorPawn::RepositionCamera()
{
	FVector NewLocation(0.f, 0.f, 0.f);
	FRotator NewRotation(0.f, 0.f, 0.f);

	float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(CameraZAngle));
	float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(CameraZAngle));

	float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(CameraHeightAngle));
	float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(CameraHeightAngle));

	NewLocation.X = cosCameraZAngle * cosCameraHeightAngle * CameraRadius;
	NewLocation.Y = sinCameraZAngle * cosCameraHeightAngle * CameraRadius;
	NewLocation.Z = sinCameraHeightAngle * CameraRadius;
	
	float TerrainSurfaceZ = GetLandTerrainSurfaceAtCoord(GetActorLocation().X + NewLocation.X, GetActorLocation().Y + NewLocation.Y);
	if (GetActorLocation().Z + NewLocation.Z < TerrainSurfaceZ + CameraHeight)
	{
		NewLocation.Z = TerrainSurfaceZ - GetActorLocation().Z + CameraHeight;
	}

	CameraComponent->SetRelativeLocation(NewLocation);
	NewRotation = (FVector(0.0f, 0.0f, 0.0f) - NewLocation).Rotation();
	CameraComponent->SetRelativeRotation(NewRotation);
}

void ARTSPlayerCameraSpectatorPawn::MoveCameraForwardInput(float Direction)
{
	if (!bCanMoveCamera)
	{
		return;
	}

	MoveForwardValue = Direction;
}


void ARTSPlayerCameraSpectatorPawn::MoveCameraRightInput(float Direction)
{
	if (!bCanMoveCamera)
	{
		return;
	}

	MoveRightValue = Direction;
}


void ARTSPlayerCameraSpectatorPawn::MoveCameraUpInput(float Direction)
{
	if (!bCanMoveCamera)
	{
		return;
	}

	MoveUpValue = Direction;
}


void ARTSPlayerCameraSpectatorPawn::ZoomCameraInInput(float Direction)
{
	if (!bCanMoveCamera)
	{
		return;
	}

	ZoomInValue = Direction;
}

FVector ARTSPlayerCameraSpectatorPawn::MoveCameraForward(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * GetIsolatedCameraYaw().Vector();
	return DeltaMovement;
}

FVector ARTSPlayerCameraSpectatorPawn::MoveCameraRight(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * (FRotator(0.0f, 90.0f, 0.0f) + GetIsolatedCameraYaw()).Vector();
	return DeltaMovement;
}

float ARTSPlayerCameraSpectatorPawn::MoveCameraUp(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	return MovementValue;
}

void ARTSPlayerCameraSpectatorPawn::ZoomCameraIn(float Direction)
{
	float MovementValue = Direction * CameraMovementSpeed;
	CameraRadius += MovementValue;
	CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);
}

void ARTSPlayerCameraSpectatorPawn::TurnCameraUp(float Direction)
{
	CameraHeightAngle -= Direction * CameraRotationSpeed * 10.0f;
	CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);
}

void ARTSPlayerCameraSpectatorPawn::TurnCameraRight(float Direction)
{
	CameraZAngle += Direction * CameraRotationSpeed * 10.0f;
}

FRotator ARTSPlayerCameraSpectatorPawn::GetIsolatedCameraYaw()
{
	// FRotator containing Yaw only
	return FRotator(0.0f, CameraComponent->GetComponentToWorld().Rotator().Yaw, 0.0f);
}

float ARTSPlayerCameraSpectatorPawn::GetLandTerrainSurfaceAtCoord(float XCoord, float YCoord) const
{
	FCollisionQueryParams TraceParams(FName(TEXT("LandTerrain")), false, this);        // TraceTag (info for debugging), bTraceComplex, AddIgnoredActor
	TraceParams.bFindInitialOverlaps = false;

	FHitResult Hit;

	FVector Start = FVector(XCoord, YCoord, GetActorLocation().Z + CameraRadius);
	FVector End = FVector(XCoord, YCoord, -500.f);

	// ECC_ channels should be set properly !!!
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_WorldStatic, TraceParams);

	if (bHit)
	{
		return Hit.ImpactPoint.Z;    // for shape trace it differs from Location
	}

	return 0.f;        // water level
}

void ARTSPlayerCameraSpectatorPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector2D MousePosition;
	FVector2D ViewportSize;
	
	if (!GEngine)
	{
		return;
	}

	UGameViewportClient* GameViewport = GEngine->GameViewport;

	// it is always nullptr on dedicated server
	if (!GameViewport)
	{
		return;
	}

	GameViewport->GetViewportSize(ViewportSize);

	// if viewport is focused, contains the mouse, and camera movement is allowed
	if (GameViewport->IsFocused(GameViewport->Viewport)
		&& GameViewport->GetMousePosition(MousePosition) && bCanMoveCamera)
	{
		if (MousePosition.X < CameraScrollBoundary)
		{
			MoveRightValue = -1.0f;
		}
		else if (ViewportSize.X - MousePosition.X < CameraScrollBoundary)
		{
			MoveRightValue = 1.0f;
		}

		if (MousePosition.Y < CameraScrollBoundary)
		{
			MoveForwardValue = 1.0f;
		}
		else if (ViewportSize.Y - MousePosition.Y < CameraScrollBoundary)
		{
			MoveForwardValue = -1.0f;
		}

		FVector ActualLocation = GetActorLocation();
		FVector ActualMovement = FVector::ZeroVector;
	
		if (RotateValue == 0.f)
		{
			ActualMovement += MoveCameraForward(MoveForwardValue * DeltaSeconds);
			ActualMovement += MoveCameraRight(MoveRightValue * DeltaSeconds);
		}
		ActualLocation += ActualMovement;

		CameraHeight += MoveCameraUp(MoveUpValue * DeltaSeconds);
		CameraHeight = FMath::Clamp(CameraHeight, CameraHeightMin, CameraHeightMax);

		float TerrainSurfaceZ = GetLandTerrainSurfaceAtCoord(ActualLocation.X, ActualLocation.Y);
		ActualLocation.Z = TerrainSurfaceZ + CameraHeight;

		ActualLocation.X = FMath::Clamp(ActualLocation.X, -CameraXYLimit, CameraXYLimit);
		ActualLocation.Y = FMath::Clamp(ActualLocation.Y, -CameraXYLimit, CameraXYLimit);

		SetActorLocation(ActualLocation);

		if (RotateValue != 0.f)
		{
			TurnCameraUp(MoveForwardValue * DeltaSeconds);
			TurnCameraRight(MoveRightValue * DeltaSeconds);
		}

		ZoomCameraIn(ZoomInValue * DeltaSeconds);
		RepositionCamera();
	}
}