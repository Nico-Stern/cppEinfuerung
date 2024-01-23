// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generate_Dungeon.generated.h"

UCLASS()
class CPPEINFUERUNG_API AGenerate_Dungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerate_Dungeon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Rooms")
	TArray<TSubclassOf<AActor>> Rooms;

	UPROPERTY(EditAnywhere)
	bool isFrontHit;
	UPROPERTY(EditAnywhere)
	bool isRightHit;
	UPROPERTY(EditAnywhere)
	bool isBackHit;
	UPROPERTY(EditAnywhere)
	bool isLeftHit;

	UPROPERTY(EditAnywhere)
	bool isFrontWall;
	UPROPERTY(EditAnywhere)
	bool isRightWall;
	UPROPERTY(EditAnywhere)
	bool isBackWall;
	UPROPERTY(EditAnywhere)
	bool isLeftWall;

	UPROPERTY(EditAnywhere)
	bool HasPlacedFront;
	UPROPERTY(EditAnywhere)
	bool HasPlacedBack;
	UPROPERTY(EditAnywhere)
	bool HasPlacedRight;
	UPROPERTY(EditAnywhere)
	bool HasPlacedLeft;

	UPROPERTY(EditAnywhere)
	int Change;
	UPROPERTY(EditAnywhere)
	int ChangeHasToBe;

	TArray<int> CanPlaced;
	int Number1=-1;
	int Number2=-1;
	int Number3=-1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> left;
	//virtual UActorComponent* FindComponentByClass(const TSubclassOf<UActorComponent> ComponentClass) const override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Right;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor>  Front;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor>  Back;

	void OneForward();
	void CheckPlace();
	void CheckGates();
	void PlaceRooms();
	void SetWalls();

	UStaticMeshComponent* MeshComponent;
	FVector MeshScale;
};
