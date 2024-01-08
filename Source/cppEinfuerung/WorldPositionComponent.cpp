// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionComponent.h"
//#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values for this component's properties
UWorldPositionComponent::UWorldPositionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPositionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	FString meinLog = TEXT("Jo was geht");

	//Gibt adresse im ram
	FString* printlog =&meinLog;

	FVector Name =GetOwner()->GetActorLocation();
	

	UE_LOG(LogTemp, Error, TEXT("Mein begin klappt! %s"), *Name.ToString());
	UE_LOG(LogTemp, Error, TEXT("Mein begin klappt! %s"), **printlog);

	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Lol"));
	
}


// Called every frame
void UWorldPositionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

