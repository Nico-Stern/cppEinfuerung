// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonListComponent.h"

// Sets default values for this component's properties
UDungeonListComponent::UDungeonListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDungeonListComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ZielLocation=FVector(8,8,8);
}


// Called every frame
void UDungeonListComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timer=Timer+ DeltaTime;
	
	if(Timer>=1)
	{
		
		SetComponentTickEnabled(false);
		SetGoalRoom();
		ZielLocation=RoomCord;

		if(GoalSphere)
		{
		 	GetWorld()->SpawnActor<AActor>(GoalSphere,ZielLocation+FVector(0,0,100),FRotator(0,0,0));	
		}
	}
	

	// ...
}

void UDungeonListComponent::AddOtherRoom(FVector RoomLocation)
{
	TestList.Add(RoomLocation);
}

void UDungeonListComponent::SetGoalRoom()
{
	int i=TestList.Num()/2;
	RoomCord= TestList[i];
}



