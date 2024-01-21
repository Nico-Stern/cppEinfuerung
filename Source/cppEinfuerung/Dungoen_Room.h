// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generate_Dungeon.h"
#include "GameFramework/Actor.h"
#include "Dungoen_Room.generated.h"

UCLASS()
class CPPEINFUERUNG_API ADungoen_Room : public AGenerate_Dungeon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungoen_Room();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
