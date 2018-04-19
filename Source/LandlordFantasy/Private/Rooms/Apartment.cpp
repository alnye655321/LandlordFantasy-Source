// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Apartment.h"


// Sets default values
AApartment::AApartment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ApartmentBoxRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ApartmentBoxRoot")); // initialize a component
	RootComponent = ApartmentBoxRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	ApartmentCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ApartmentCollisionBox"));
	ApartmentCollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	ApartmentCollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	ApartmentCollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	ApartmentCollisionBox->AttachToComponent(ApartmentBoxRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void AApartment::BeginPlay()
{
	//Super::BeginPlay();
	
}

// Called every frame
void AApartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

