// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}	


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	OpenDoor= GetOwner()->GetActorRotation();
	StartDoor=OpenDoor;
	Endstate.Yaw= OpenDoor.Yaw+TargetYaw;
	a=GetOwner()->GetActorRotation();
	ActorThatCanOpen=GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!OpenDoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("KEIN TRIGGER GESETZT"));
	}
	CurrentTimer=0;
	
	if(!OpenDoorSound)
	{
		//Print nicht zugewiesen;
	}
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(OpenDoorTrigger&&(OpenDoorTrigger->IsOverlappingActor(ActorThatCanOpen)||GetTotalMassOfActors()>=MassNeeded))
	{
		OpenTheDoor(DeltaTime);
		CurrentTimer=CloseTimer;
	}
	else if(OpenDoorTrigger&&( !OpenDoorTrigger->IsOverlappingActor(ActorThatCanOpen)||GetTotalMassOfActors()<MassNeeded)&&CurrentTimer<=0)
	{
		CloseTheDoor(DeltaTime);
	}
	CurrentTimer-=DeltaTime;

	
	// ...
	
}

void UOpenDoor::OpenTheDoor(float b)
{
	OpenDoor= GetOwner()->GetActorRotation();
	nee= FMath::Lerp(OpenDoor.Yaw,Endstate.Yaw,SpeedDoor*b);
	a.Yaw=nee;
	GetOwner()->SetActorRotation(a,ETeleportType::None);
}

void UOpenDoor::CloseTheDoor(float b)
{
	OpenDoor= GetOwner()->GetActorRotation();
	nee= FMath::Lerp(OpenDoor.Yaw,StartDoor.Yaw,SpeedDoor*b);
	a.Yaw=nee;
	GetOwner()->SetActorRotation(a,ETeleportType::None);
}

float UOpenDoor::GetTotalMassOfActors()
{
	float TotalMass=0.f;
	TArray<AActor*>OverlappingActors;
	OpenDoorTrigger->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}

void UOpenDoor::PlayOpenDoorSound()
{
	if(OpenDoorSound)
	{
		OpenDoorSound->Play();
	}
}


