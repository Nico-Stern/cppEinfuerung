// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"

#include "GoalActor.h"

// Sets default values for this component's properties
UGoal::UGoal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoal::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGoal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IsGoalOpen= CheckSphere(Trigger, GoalSphere);
	if(IsGoalOpen)
	{
	}
}

bool UGoal::CheckSphere(TArray<ATriggerSphere*> TriggerSpheres, TArray<AActor*> GoalSpheres)
{
	//check All Spheres
	for(int i=0; TriggerSpheres.Num()>i;i++)
	{
		for(int j=0; GoalSpheres.Num()>j;j++)
		{
			
			if(TriggerSpheres[i]->IsOverlappingActor(GoalSpheres[j]))
			{
				UE_LOG(LogTemp, Error, TEXT("true"));
				IsInGoal=true;
				break;
			}
		}
		if(!IsInGoal)
		{
			break;
		}
	}

	//Catch GoalSpheres
	for(int i=0; TriggerSpheres.Num()>i;i++)
	{
		for(int j=0; GoalSpheres.Num()>j;j++)
		{
			
			if(TriggerSpheres[i]->IsOverlappingActor(GoalSpheres[j]))
			{
				GoalSpheres[j]->DisableComponentsSimulatePhysics();
			}
		}
	}
	
	if(IsInGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Win"));
		GetOwner()->Destroy();
		return true;
	}

	TArray<AActor*> CatchedObjects;
	//float CatchedMass;
	TriggerSpheres[0]->GetOverlappingActors(CatchedObjects);

	for (int i=0;i<CatchedObjects.Num();i++)
	{
		if(Cast<AGoalActor>(CatchedObjects[i]))
		{
			CatchedObjects[i]->Destroy();
			GetOwner()->Destroy();
		}
	}
	
	return false;
}



