// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Seat.h"


// Sets default values
ASeat::ASeat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SeatRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Seat")); // initialize a component
	RootComponent = SeatRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(SeatRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

	XSpot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XSpot"));
	XSpot->AttachToComponent(SeatRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	XSpot->SetHiddenInGame(true);//only show in editor for placement

}

// Called when the game starts or when spawned
void ASeat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASeat::GetLocationVec()
{
	return CollisionBox->GetComponentLocation();
}

FVector ASeat::GetXSpotLocation()
{
	FVector XSpotLocation = XSpot->GetComponentLocation();
	return XSpotLocation;
}

FRotator ASeat::GetXSpotRotation()
{
	FRotator XSpotRotation = XSpot->GetComponentRotation();
	return XSpotRotation;
}


