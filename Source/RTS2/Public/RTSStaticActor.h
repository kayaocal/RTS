#pragma once

#include "Components/StaticMeshComponent.h"
#include "RTSActor.h"
#include "RTSStaticActor.generated.h"

UCLASS()
class RTS2_API ARTSStaticActor : public ARTSActor
{
    GENERATED_BODY()
public:
    ARTSStaticActor();
    UStaticMeshComponent* ItemStaticMesh = nullptr;

};

