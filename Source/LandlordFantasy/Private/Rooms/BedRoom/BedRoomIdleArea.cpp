// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "BedRoomIdleArea.h"
#include "NPCs/Characters/Lucy.h"


// Sets default values
ABedRoomIdleArea::ABedRoomIdleArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABedRoomIdleArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABedRoomIdleArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


