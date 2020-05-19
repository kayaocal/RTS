#include "RTS2/Public/RTSSkeletalActor.h"

#include "RTS2/Prerequisites.h"

ARTSSkeletalActor::ARTSSkeletalActor()
{
	IsSkeletal = true;
	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	ItemSkeletalMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	ItemSkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	SelectionPlaneComponent->AttachToComponent(ItemSkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);
	
    Pawnmovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("movement component"));
	Pawnmovement->UpdatedComponent = RootComponent;
	AutoPossessAI = EAutoPossessAI::Spawned;
}

void ARTSSkeletalActor::MoveActor(FVector_NetQuantize* TargetPos)
{
	int intVar = TargetPos->X;
	float floatVar = 3.7f;
	FString fstringVar = "MoveUnitsToPosition IF";
	
	NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
    // APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
    TArray<FVector> Locations;
    if (NavSystem){
        /*FPathFindingQuery Query;
        FAIMoveRequest MoveReq;
        FNavPathSharedPtr OutPath;
        //MoveReq.SetGoalLocation(Hit.Location);
    	// FVector PathTargetPosition;
    	// PathTargetPosition.X = TargetPos->X;
    	// PathTargetPosition.Y = TargetPos->Y;
    	// PathTargetPosition.Z = TargetPos->Z;
        MoveReq.SetGoalLocation(*TargetPos);
  
        fstringVar = "MoveActor() ";
        intVar = TargetPos->X;
        UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar );
    	intVar = MoveReq.GetGoalLocation().X;
    	UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar );
    	
        AAIController* AiCtrl = Cast<AAIController>(GetController());
        if(AiCtrl != nullptr)
        {
        	AiCtrl->BuildPathfindingQuery(MoveReq, Query);
        	//AiCtrl->PreparePathfinding(MoveReq, Query);
        }
    	
        FPathFindingResult PathFindingResult = NavSystem->FindPathSync(Query);
    	
    	fstringVar = "Path info ";
    	if(PathFindingResult.Path != nullptr)
    	{
    		UE_LOG(LogTemp, Warning, TEXT("Text, %d %d %s"), PathFindingResult.IsSuccessful(), PathFindingResult.Path->IsValid(), *fstringVar );
    	}
    	
         // if (PathFindingResult.IsSuccessful() && PathFindingResult.Path->IsValid()){
         // 	
         // 	for (auto &PathPoint : PathFindingResult.Path->GetPathPoints()){
         // 		Locations.Add(PathPoint.Location);
         // 	}
         // }*/
         AAIController* AiCtrl = Cast<AAIController>(GetController());
         if(AiCtrl != nullptr)
        {
    		//AiCtrl->MoveTo(MoveReq , &OutPath);

         	AiCtrl->MoveToLocation(FVector(TargetPos->X, TargetPos->Y, TargetPos->Z),0,false,true,false,true,0,false);
         	FString fstringVar2 = "IS FALLOWING PATH ";
         	UE_LOG(LogTemp, Warning, TEXT("Text, %d  %s"), AiCtrl->IsFollowingAPath(), *fstringVar2 );
        }
    }
}