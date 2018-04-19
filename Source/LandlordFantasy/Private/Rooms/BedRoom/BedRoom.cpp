// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "Rooms/Globals/Items/Seat.h"
#include "BedRoom.h"


// Sets default values
ABedRoom::ABedRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BedRoomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BedRoomBox")); // initialize a component
	RootComponent = BedRoomRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(BedRoomRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void ABedRoom::BeginPlay()
{
	//Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABedRoom::OnPlayerEnterPickupBox); // begin overlap
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABedRoom::OnPlayerLeavePickupBox); // end overlap
	
}

// Called every frame
void ABedRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABedRoom::getLocationVec()
{
	return LocationVec;
}

// triggers enter bedroom room change in npc character
void ABedRoom::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "bedroom");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		PossibleNpc->setInBedRoom(true);

		int32 randomActorClass = 0;//!!! set to random number here when adding more interactable actors

		if (randomActorClass == 0)
		{
			TArray <AActor*> OverlappingActors;
			GetOverlappingActors(OverlappingActors);
			//should set another random number here based on total number of actors
			for (auto Seat : OverlappingActors)
			{
				ASeat* PossibleChair = Cast<ASeat>(Seat);
				if (PossibleChair != NULL)
				{
					PossibleNpc->SetTarget(Seat);
					FVector ChairSitdownLocation = PossibleChair->GetLocationVec();
					PossibleNpc->SetTargetVector(ChairSitdownLocation);
				}

			}


		}
	}

	//GetOverlappingActors(OverlappingActors);//return all overlapping actors

}

// triggers leave bedroom room change in npc character
void ABedRoom::OnPlayerLeavePickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "leave bedroom");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		PossibleNpc->setInBedRoom(false);
	}

}

void ABedRoom::FindSeat(float HealValue)
{
	TArray<AActor*> SeatsInZone;

	GetOverlappingActors(SeatsInZone, TSubclassOf<ANpc>()); // need to change & crate Seat class

	for (auto Seat : SeatsInZone)
	{

	}
}

