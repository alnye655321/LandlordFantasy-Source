// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "Rooms/Globals/Items/Seat.h"
#include "Rooms/IdleArea.h"
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

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABedRoom::OnPlayerEnterPickupBox);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABedRoom::OnPlayerLeavePickupBox);
	
}

// Called every frame
void ABedRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// triggers enter bedroom room change in npc character
void ABedRoom::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "bedroom");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		FString Room = "BedRoom";
		PossibleNpc->SetRoom(Room);		

		//int32 randIndex = FMath::RandRange(0, FoundActors.Num() - 1);

		TArray <AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors); //get all actors in bedroom

		for (auto OverLappedActor : OverlappingActors)
		{
			ASeat* PossibleChair = Cast<ASeat>(OverLappedActor);
			if (PossibleChair != NULL)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "NPCOverlapbedroom");
				Seats.Add(PossibleChair);
			}				

			AIdleArea* PossibleIdleSpot = Cast<AIdleArea>(OverLappedActor);
			if (PossibleIdleSpot != NULL)
				IdleAreas.Add(PossibleIdleSpot);

		}

		BedRoomInteract(PossibleNpc);

		//for (auto Seat : OverlappingActors)
		//{
		//	ASeat* PossibleChair = Cast<ASeat>(Seat);
		//	if (PossibleChair != NULL)
		//	{
		//		PossibleNpc->SetTarget(Seat);
		//		FVector ChairSitdownLocation = PossibleChair->GetLocationVec();
		//		PossibleNpc->SetTargetVector(ChairSitdownLocation);
		//	}
		//}


		
	}

	//GetOverlappingActors(OverlappingActors);//return all overlapping actors

}

void ABedRoom::BedRoomInteract(ANpc* MyNpc)
{
	int32 TotalRoomActions = Seats.Num() + IdleAreas.Num(); //!!! should be a parent interactable class for all

	int32 RandIndex = FMath::RandRange(0, 1);

	switch (RandIndex)
	{
	case 0:
		if (Seats.Num() > 0)
		{
			int32 VarIndex = FMath::RandRange(0, Seats.Num() - 1);
			MyNpc->SetTarget(Seats[VarIndex]); //updates npc, AI, then Target<Object> blackboard
			MyNpc->SetAction("Sit");
		}

		break;

	case 1:
		if (IdleAreas.Num() > 0)
		{
			int32 VarIndex = FMath::RandRange(0, IdleAreas.Num() - 1);
			MyNpc->SetTarget(IdleAreas[VarIndex]);
			MyNpc->SetAction("Idle");
		}

		break;

	default:
		break;//could be an idle for default???
	}

}
// triggers leave bedroom room change in npc character
void ABedRoom::OnPlayerLeavePickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "leave bedroom");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
	}

}




