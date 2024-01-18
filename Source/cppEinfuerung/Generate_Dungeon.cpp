// Fill out your copyright notice in the Description page of Project Settings.


#include "Generate_Dungeon.h"

#include "K2Node_SpawnActor.h"
#include "K2Node_SpawnActorFromClass.h"

// Sets default values
AGenerate_Dungeon::AGenerate_Dungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenerate_Dungeon::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RoomGenerator"));
	MeshComponent= FindComponentByClass<UStaticMeshComponent>();
	FVector MeshScale= MeshComponent->GetComponentScale();
	UE_LOG(LogTemp, Error, TEXT("Actor Component %f"), MeshScale.X);

	FVector MeshLocation= MeshComponent->GetComponentLocation();
	float a= MeshScale.X/2*100 + MeshLocation.X;
	const FVector test=FVector(a,0,0);
	//const FVector lel = GetOwner()->GetActorLocation()+test;
	FRotator testa= FRotator(0,0,0);
	if(Rooms[0])
	{
		GetWorld()->SpawnActor<AActor>(*Rooms[0],test, testa);
	}
}

// Called every frame
void AGenerate_Dungeon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

