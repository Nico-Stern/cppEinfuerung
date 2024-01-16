// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerSphere.h"
#include "Goal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPEINFUERUNG_API UGoal : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category="TriggerSphere")
	TArray<ATriggerSphere*> Trigger;

	UPROPERTY(EditAnywhere, Category="GoalSpheres")
	TArray<AActor*> GoalSphere;

	UPROPERTY(EditAnywhere, Category="BoolCheck")
	bool IsInGoal;

	bool IsGoalOpen;

	bool CheckSphere(TArray<ATriggerSphere*> TriggerSpheres,TArray<AActor*> GoalSpheres);
};
