// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Bed.h"

// Sets default values
ABed::ABed()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Seat")); // initialize a component
	RootComponent = BedRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(BedRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component


}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABed::GetXSpotLocation()
{
	//FVector XSpotLocation = XSpot->GetComponentLocation();
	return XSpotLocation;
}

void ABed::SetXSpotLocation(FVector NewLocation)
{
	XSpotLocation = NewLocation;
}

FRotator ABed::GetXSpotRotation()
{
	//FRotator XSpotRotation = XSpot->GetComponentRotation();
	return XSpotRotation;
}

void ABed::SetXSpotRotation(FRotator NewRotation)
{
	XSpotRotation = NewRotation;
}




