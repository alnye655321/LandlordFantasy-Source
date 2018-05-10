// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "DoorActor.h"
#include "NPCs/Npc.h"


// Sets default values
ADoorActor::ADoorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ADoorActor::GetXSpotLocation()
{
	return XSpotLocation;
}

void ADoorActor::SetXSpotLocation(FVector NewLocation)
{
	XSpotLocation = NewLocation;
}

FRotator ADoorActor::GetXSpotRotation()
{
	//FRotator XSpotRotation = XSpot->GetComponentRotation();
	return XSpotRotation;
}

void ADoorActor::SetXSpotRotation(FRotator NewRotation)
{
	XSpotRotation = NewRotation;
}

