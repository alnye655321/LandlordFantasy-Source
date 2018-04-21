// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "IdleArea.h"


// Sets default values
AIdleArea::AIdleArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IdleRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Seat")); // initialize a component
	RootComponent = IdleRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(IdleRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

	XSpot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XSpot"));
	XSpot->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	XSpot->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	XSpot->SetHiddenInGame(true);//only show in editor for placement
	XSpot->bGenerateOverlapEvents = false;
	XSpot->AttachToComponent(IdleRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	Arrow->SetRelativeLocation(FVector(1.0f, 1.0f, 3.0f));// relative to parent root
	Arrow->SetHiddenInGame(true);//only show in editor for placement
	Arrow->bGenerateOverlapEvents = false;
	Arrow->AttachToComponent(IdleRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}
//FVector XSpotLocation;
//FRotator XSpotRotation;
// Called when the game starts or when spawned
void AIdleArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIdleArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AIdleArea::GetXSpotLocation()
{
	return XSpotLocation;
}

void AIdleArea::SetXSpotLocation(FVector NewLocation)
{
	XSpotLocation = NewLocation;
}

FRotator AIdleArea::GetXSpotRotation()
{
	return XSpotRotation;
}

void AIdleArea::SetXSpotRotation(FRotator NewRotation)
{
	XSpotRotation = NewRotation;
}

