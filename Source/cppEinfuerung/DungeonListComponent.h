// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Goal.h"
#include "DungeonListComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPEINFUERUNG_API UDungeonListComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonListComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category="RoomListHolder")
	TArray<FVector> TestList={};

	UPROPERTY(EditAnywhere, Category="GoalSphere")
	TSubclassOf<AActor> GoalSphere;

	UPROPERTY(EditAnywhere, Category="GoalSphere")
	FVector ZielLocation;

	FVector RoomCord;
	
	UPROPERTY(EditAnywhere, Category="GoalSphere")
	float Timer;

	void AddOtherRoom(FVector);

	void SetGoalRoom();
};
