// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "LivingRoom.h"


// Sets default values
ALivingRoom::ALivingRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LivingRoomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LivingRoomTriggerBox")); // initialize a component
	RootComponent = LivingRoomRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(LivingRoomRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void ALivingRoom::BeginPlay()
{
	//Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALivingRoom::OnPlayerEnterPickupBox); // on the overlap
	
}

// Called every frame
void ALivingRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ALivingRoom::getLocationVec()
{
	return LocationVec;
}

// triggers in living room change in npc character
void ALivingRoom::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "livingroom");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
	}


}

