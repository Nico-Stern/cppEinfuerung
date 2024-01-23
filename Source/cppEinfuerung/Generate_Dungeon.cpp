 // Fill out your copyright notice in the Description page of Project Settings.


#include "Generate_Dungeon.h"

#include "CollisionDebugDrawingPublic.h"

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
	

	CheckPlace();
	
	CheckGates();

	PlaceRooms();

	SetWalls();
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
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	
	isFrontHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitForward, GetActorLocation(), GetActorLocation()+FVector(MeshScale.X*400,0,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);
	isBackHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitBack, GetActorLocation(), GetActorLocation()-FVector(MeshScale.X*400,0,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);
	isLeftHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitLeft, GetActorLocation(), GetActorLocation()-FVector(0,MeshScale.X*400,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);
	isRightHit= GetWorld() -> LineTraceSingleByObjectType(OUT HitRight, GetActorLocation(), GetActorLocation()+FVector(0,MeshScale.X*400,0), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);
	
	
	if(isLeftHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LeftHit"));
	}
	else
	{
		CanPlaced.Add(3);
	}
	if(isBackHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BackHit"));
	}
	else
	{
		CanPlaced.Add(2);
	}
	if(isRightHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RightHit"));
	}
	else
	{
		CanPlaced.Add(1);
	}

	if(isFrontHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FrontHit"));
	}
	else
	{
		CanPlaced.Add(0);
	}
}

void AGenerate_Dungeon::PlaceRooms()
{
	if(CanPlaced.Num()>0)
	{
		int j=FMath::RandRange(0,4);
		Number1 = j;
		{
			int k=FMath::RandRange(0,4);
			Number2=k;
			{
				int l=FMath::RandRange(0,4);
				Number3=l;
				if(Number1==Number3&&Number2==Number3)
				{
					//schleife
				}
			}
		}
	}

	if((Number1==0||Number2==0||Number3==0)&!isFrontHit)
	{
		GetWorld()->SpawnActor<AActor>(Rooms[1],GetActorLocation()+FVector(MeshScale.X*400,0,0),GetActorRotation());
		HasPlacedFront=true;
	}
	else if(!isFrontHit)
	{
		GetWorld()->SpawnActor<AActor>(Front,GetActorLocation(),GetActorRotation());
	}
	
	

	if((Number1==1||Number2==1||Number3==1)&!isLeftHit)
	{
		GetWorld()->SpawnActor<AActor>(Rooms[1],GetActorLocation()-FVector(0,MeshScale.X*400,0),GetActorRotation());
		HasPlacedLeft=true;
	}
	else if(!isLeftHit)
	{
		GetWorld()->SpawnActor<AActor>(left,GetActorLocation(),GetActorRotation());
	}
	
	
	if((Number2==2||Number1==2||Number3==2)&!isBackHit)
	{
		GetWorld()->SpawnActor<AActor>(Rooms[1],GetActorLocation()-FVector(MeshScale.X*400,0,0),GetActorRotation());
		HasPlacedBack=true;
	}
	else if(!isBackHit)
	{
		GetWorld()->SpawnActor<AActor>(Back,GetActorLocation(),GetActorRotation());
	}
	
	
	
	if((Number2==3||Number1==3||Number3==3)&!isRightHit)
	{
		GetWorld()->SpawnActor<AActor>(Rooms[1],GetActorLocation()+FVector(0,MeshScale.X*400,0),GetActorRotation());
		HasPlacedRight=true;
	}
	else if(!isRightHit)
	{
		GetWorld()->SpawnActor<AActor>(Right,GetActorLocation(),GetActorRotation());
	}
}

void AGenerate_Dungeon::CheckGates()
{
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	FHitResult Hit;
	if(isBackHit)
	{
		isBackWall= GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetActorLocation()+FVector(0,0,50), GetActorLocation()-FVector(MeshScale.X*400,0,-50), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);
		
	}
	if(isFrontHit)
	{
		isFrontWall= GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetActorLocation()+FVector(0,0,50), GetActorLocation()+FVector(MeshScale.X*400,0,50), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);

	}
	if(isLeftHit)
	{
		isLeftWall= GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetActorLocation()+FVector(0,0,50), GetActorLocation()-FVector(0,MeshScale.X*400,-50), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);

	}
	if(isRightHit)
	{
		isRightWall= GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetActorLocation()+FVector(0,0,50), GetActorLocation()+FVector(0,MeshScale.X*400,50), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),TraceParams);

	}

	if(isFrontHit&!isFrontWall)
	{
		
	}
}

void AGenerate_Dungeon::SetWalls()
{
	if(!HasPlacedLeft&&(!isLeftHit))
	{
		GetWorld()->SpawnActor<AActor>(left,GetActorLocation(),GetActorRotation());
	}
	if(!HasPlacedRight&&(!isRightHit))
	{
		GetWorld()->SpawnActor<AActor>(Right,GetActorLocation(),GetActorRotation());
	}
	if(!HasPlacedFront&&(!isFrontHit))
	{
		GetWorld()->SpawnActor<AActor>(Front,GetActorLocation(),GetActorRotation());
	}
	if(!HasPlacedBack&&(!isBackHit))
	{
		GetWorld()->SpawnActor<AActor>(Back,GetActorLocation(),GetActorRotation());
	}

	if(isBackHit&&isFrontHit&&isLeftHit&&isRightHit)
	{
		PlaceRooms();
	}
}

