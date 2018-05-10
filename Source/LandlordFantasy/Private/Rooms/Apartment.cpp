// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
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

	ApartmentCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AApartment::OnPlayerEnterPickupBox);
	ApartmentCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AApartment::OnPlayerLeavePickupBox);
	
}

// Called every frame
void AApartment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AApartment::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//SendToRoom(OtherActor);
}


void AApartment::SendToRoom(AActor * OtherActor)
{
	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		TArray <AActor*> OverlappingRooms;

		GetOverlappingActors(OverlappingRooms); //get all rooms in this apartment

		for (auto OverlappingRoom : OverlappingRooms)
		{
			ARoom* PossibleRoom = Cast<ARoom>(OverlappingRoom);

			if (PossibleRoom != NULL)
				RoomsInApartment.Add(PossibleRoom);
		}

		PossibleNpc->ChooseRoomDestination(RoomsInApartment);

	}
}

void AApartment::OnPlayerLeavePickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}