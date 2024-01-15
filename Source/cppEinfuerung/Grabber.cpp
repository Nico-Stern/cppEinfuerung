// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Error, TEXT("Hallo, bin der Grabber"));

	MyPhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if(!MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Kein Physichandel gefunen"));
	}

	SetupComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//FVector LineTraceEnd = PlayerPOVLocation + PlayerPOVRotator.Vector()*TraceLength;

	if(MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->SetTargetLocation(GetEndLineTrace());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB"));

	if(GetWorld())
	{
		FHitResult Hit;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
		GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetPlayerViewPointLocationStart(), GetEndLineTrace(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParams); 

		AActor* ActorHit = Hit.GetActor();
		if(ActorHit)
		{
			UE_LOG(LogTemp, Error, TEXT("Actor Hit: %s"), *(ActorHit->GetName()));
			MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(),NAME_None, GetEndLineTrace());
		}
	}
	
}

void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB_RELEASED"));

	if(MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::SetupComponent()
{
	MyInputComponent=GetOwner()->FindComponentByClass<UInputComponent>();

	if (MyInputComponent)
	{
		MyInputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
		MyInputComponent->BindAction("Grab",IE_Released, this, &UGrabber::GrabRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Kein UInput gefunen"));
	}
}

FVector UGrabber::GetPlayerViewPointLocationStart()
{
	if(GetWorld())
	{
		FVector PlayerPOVLocation;
		FRotator PlayerPOVRotator;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPOVLocation, OUT PlayerPOVRotator);
		return PlayerPOVLocation;
	}
	else
	{
		return FVector(0,0,0);
	}
}

FVector UGrabber::GetEndLineTrace()
{
	if(GetWorld())
	{
		FVector PlayerPOVLocation;
		FRotator PlayerPOVRotator;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPOVLocation, OUT PlayerPOVRotator);
		return  PlayerPOVLocation+PlayerPOVRotator.Vector()*TraceLength;
	}
	else
	{
		return FVector (0,0,0);
	}
}



