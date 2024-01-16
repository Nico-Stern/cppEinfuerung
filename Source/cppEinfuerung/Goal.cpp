// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"

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
}

bool UGoal::CheckSphere(TArray<ATriggerSphere*> TriggerSpheres, TArray<AActor*> GoalSpheres)
{
	for(int i=0; TriggerSpheres.Num()>i;i++)
	{
		//UE_LOG(LogTemp, Error, TEXT("Testet"));
		for(int j=0; GoalSpheres.Num()>j;j++)
		{
			if(TriggerSpheres[i]->IsOverlappingActor(GoalSpheres[j]))
			{
				//UE_LOG(LogTemp, Error, TEXT("true"));
				IsInGoal=true;
				break;
			}
			else
			{
				IsInGoal=false;
			}
		}
		if(!IsInGoal)
		{
			break;
		}
		
	}
	if(IsInGoal)
	{
		UE_LOG(LogTemp, Error, TEXT("true"));
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("false"));
	return false;
}



