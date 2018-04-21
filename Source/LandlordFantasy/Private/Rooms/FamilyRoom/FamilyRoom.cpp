// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "FamilyRoom.h"


// Sets default values
AFamilyRoom::AFamilyRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FamilyRoomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FamilyRoomTriggerBox")); // initialize a component
	RootComponent = FamilyRoomRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(FamilyRoomRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void AFamilyRoom::BeginPlay()
{
	//Super::BeginPlay();

	LocationVec = GetActorLocation();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFamilyRoom::OnPlayerEnterPickupBox); // on the overlap
	
}

// Called every frame
void AFamilyRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AFamilyRoom::getLocationVec()
{
	return LocationVec;
}

// triggers in family room change in npc character
void AFamilyRoom::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "family room box");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
	}


}
