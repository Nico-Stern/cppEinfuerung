 // Fill out your copyright notice in the Description page of Project Settings.


#include "Generate_Dungeon.h"

#include "CollisionDebugDrawingPublic.h"
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
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	FVector TESTT	= MeshComponent->GetComponentScale();
	MeshScale=TESTT;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RoomGenerator"));

	OneForward();
	OneForward();
	OneForward();

	CheckPlace();
}

// Called every frame
void AGenerate_Dungeon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGenerate_Dungeon::OneForward()
{
	
	UE_LOG(LogTemp, Error, TEXT("Actor Component %f"), MeshScale.X);

	FVector MeshLocation= MeshComponent->GetComponentLocation();
	float a= MeshScale.X/2*100 + MeshLocation.X;
	float b=MeshScale.X*100;
	const FVector test=FVector(a,0,0);
	const FVector testb= FVector(b,0,0);
	const FVector testc= FVector(0,b,0);
	const FVector lel = GetActorLocation();
	FRotator testa= FRotator(0,0,0);
	FRotator testQ= FRotator(0,90,0);
	if(Rooms[0])
	{
		
		if(GetActorRotation().Yaw==0.f)
		{
			GetWorld()->SpawnActor<AActor>(*Rooms[0],lel, testa);
			SetActorLocation(lel-testb);
		}
		if(GetActorRotation().Yaw<=180.f&&GetActorRotation().Yaw>=179.f)
		{
			GetWorld()->SpawnActor<AActor>(*Rooms[0],lel, testa);
			SetActorLocation(lel+testb);
		}
		if(GetActorRotation().Yaw<=90.f&&GetActorRotation().Yaw>=89.f)
		{
			GetWorld()->SpawnActor<AActor>(*Rooms[0],lel, testQ);
			SetActorLocation(lel-testc);
		}
		if(GetActorRotation().Yaw>=-90.f&&GetActorRotation().Yaw<=-89.f)
		{
			GetWorld()->SpawnActor<AActor>(*Rooms[0],lel, testQ);
			SetActorLocation(lel+testc);
		}
	}
}

void AGenerate_Dungeon::CheckPlace()
{
	//FHitResult Hit;
	FHitResult HitForward;
	FHitResult HitRight;
	FHitResult HitBack;
	FHitResult HitLeft;
	FCollisionQueryParams TraceParams(FName(TEXT("Test")), false, GetOwner());
	isFrontHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitForward, GetActorLocation(), GetActorLocation()+FVector(MeshScale.X*100,0,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),TraceParams);
	isBackHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitBack, GetActorLocation(), GetActorLocation()-FVector(MeshScale.X*100,0,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),TraceParams);
	isLeftHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitLeft, GetActorLocation(), GetActorLocation()-FVector(0,MeshScale.X*100,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),TraceParams);
	isRightHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitRight, GetActorLocation(), GetActorLocation()+FVector(0,MeshScale.X*100,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),TraceParams);
	if(isLeftHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LeftHit"));
	}
	if(isBackHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BackHit"));
	}
	if(isFrontHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FrontHit"));
	}
	if(isRightHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RightHit"));
	}
}



