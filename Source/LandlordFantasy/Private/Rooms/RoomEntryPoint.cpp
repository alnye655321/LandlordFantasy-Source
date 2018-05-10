// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "RoomEntryPoint.h"


// Sets default values
ARoomEntryPoint::ARoomEntryPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomEntryTriggerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RoomEntryTriggerRoot")); // initialize a component
	RootComponent = RoomEntryTriggerRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(RoomEntryTriggerRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

}

// Called when the game starts or when spawned
void ARoomEntryPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomEntryPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

