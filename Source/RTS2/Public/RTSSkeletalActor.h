#pragma once

#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "RTSActor.h"
#include "RTSSkeletalActor.generated.h"
UCLASS()
class ARTSSkeletalActor : public ARTSActor
{
    GENERATED_BODY()
public:
    ARTSSkeletalActor();
    UFloatingPawnMovement* Pawnmovement;
	UNavigationSystemV1* NavSystem;
    USkeletalMeshComponent* ItemSkeletalMesh = nullptr;
    void MoveActor(FVector_NetQuantize* TargetPos);
    
};
