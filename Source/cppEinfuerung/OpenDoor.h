// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBox.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPEINFUERUNG_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	
	UPROPERTY(EditAnywhere, Category="Door Yaw")
	float TargetYaw=90;
	
	UPROPERTY(EditAnywhere, Category="Speed")
	float SpeedDoor;
	float nee;
	
	UPROPERTY(EditAnywhere, Category="TriggerBox")
	ATriggerBox* OpenDoorTrigger;

	UPROPERTY(EditAnywhere, Category="Player")
	AActor* ActorThatCanOpen;

	UPROPERTY(EditAnywhere, Category="DoorCloseDelay")
	float CloseTimer;
	float CurrentTimer;

	UPROPERTY(EditAnywhere)
	float MassNeeded;

	UPROPERTY(EditAnywhere, Category="Audio")
	UAudioComponent* OpenDoorSound;

	void PlayOpenDoorSound();
	
	FRotator OpenDoor;
	FRotator StartDoor;
	FRotator Endstate;
	FRotator a;
    bool WasInCollider;

	void OpenTheDoor(float a);
	void CloseTheDoor(float a);

private:
	float GetTotalMassOfActors();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
