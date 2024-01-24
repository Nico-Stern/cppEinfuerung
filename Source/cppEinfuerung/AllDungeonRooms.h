// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AllDungeonRooms.generated.h"

UCLASS()
class CPPEINFUERUNG_API AAllDungeonRooms : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAllDungeonRooms();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category="Rooms")
	TArray<AActor*> RoomsList;

};
