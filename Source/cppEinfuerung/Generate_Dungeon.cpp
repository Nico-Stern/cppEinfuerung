// Fill out your copyright notice in the Description page of Project Settings.


#include "Generate_Dungeon.h"

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
}

// Called every frame
void AGenerate_Dungeon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

