// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "IndoorTriggerBox.h"


// Sets default values
AIndoorTriggerBox::AIndoorTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIndoorTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

