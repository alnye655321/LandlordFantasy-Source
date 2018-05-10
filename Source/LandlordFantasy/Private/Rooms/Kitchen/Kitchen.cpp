// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Kitchen.h"
#include "NPCs/Npc.h"
#include "Kitchen.h"
#include "Rooms/IdleArea.h"
#include "Rooms/Globals/Items/Seat.h"
#include "Rooms/RoomEntryPoint.h"

// Sets default values
AKitchen::AKitchen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KitchenTriggerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("KitchenTriggerRoot")); // initialize a component
	RootComponent = KitchenTriggerRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(KitchenTriggerRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void AKitchen::BeginPlay()
{
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AKitchen::OnPlayerEnterPickupBox); // on the overlap

	//set entry point as X Spot RoomEntryPoint actor - will use for move to AI actions entering room
	TArray <AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors);

	for (auto OverlappingActor : OverlappingActors)
	{
		ARoomEntryPoint* PossibleEntryPoint = Cast<ARoomEntryPoint>(OverlappingActor);

		if (PossibleEntryPoint != NULL)
		{
			SetXSpotLocation(PossibleEntryPoint);
			break;
		}

	}


}

// Called every frame
void AKitchen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// triggers in kitchen change in npc character
void AKitchen::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "kitchen box");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL && PossibleNpc->GetDesiredRoom() == "Kitchen")
	{
		FString AIFindRoom = "found";
		PossibleNpc->SetAIFindRoom(AIFindRoom); //no longer looking for rooms in BT

		FString Room = "Kitchen";
		PossibleNpc->SetRoom(Room);

		TArray <AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors); //get all actors in kitchen

		for (auto OverLappedActor : OverlappingActors)
		{
			ASeat* PossibleChair = Cast<ASeat>(OverLappedActor);
			if (PossibleChair != NULL)
				Seats.Add(PossibleChair);

			AIdleArea* PossibleIdleSpot = Cast<AIdleArea>(OverLappedActor);
			if (PossibleIdleSpot != NULL)
				IdleAreas.Add(PossibleIdleSpot);
		}
	}

}

void AKitchen::KitchenInteract(ANpc* MyNpc, UObject* LastTarget)
{
	int32 TotalRoomActions = Seats.Num() + IdleAreas.Num();
	
	int32 RandIndex = FMath::RandRange(0, 1);
	//int32 RandIndex = 2;

	switch (RandIndex)
	{
	case 0:
		if (Seats.Num() > 0)
		{
			int32 VarIndex;

			if (Seats.Num() == 1) //RandRange won't work with no range
				VarIndex = 0;
			else
				VarIndex = FMath::RandRange(0, Seats.Num() - 1);

			FString Action = "Sit";
			NewTargetAction(LastTarget, VarIndex, MyNpc, Action);
		}

		break;

	case 1:
		if (IdleAreas.Num() > 0)
		{
			int32 VarIndex;

			if ((IdleAreas.Num() == 1))
				VarIndex = 0;
			else
				VarIndex = FMath::RandRange(0, IdleAreas.Num() - 1);

			FString Action = "Idle";
			NewTargetAction(LastTarget, VarIndex, MyNpc, Action);
		}

		break;

	default:
		break;
	}

}


//make sure we're not going to the same object twice in a row
void AKitchen::NewTargetAction(UObject * LastTarget, const int32 &VarIndex, ANpc * MyNpc, FString Action)
{
	TArray <AActor*> InteractableArray;

	if (Action == "Sit")
		InteractableArray = Seats;
	else if (Action == "Idle")
		InteractableArray = IdleAreas;

	if (LastTarget != InteractableArray[VarIndex])
	{
		MyNpc->SetTarget(InteractableArray[VarIndex]); //updates npc, AI, then Target<Object> blackboard
		MyNpc->SetAction(Action);
	}
	else
	{
		if ((VarIndex + 1) < (InteractableArray.Num() - 1))
		{
			MyNpc->SetTarget(InteractableArray[VarIndex + 1]);
			MyNpc->SetAction(Action);
		}
		else if ((VarIndex - 1) > -1)
		{
			MyNpc->SetTarget(InteractableArray[VarIndex - 1]);
			MyNpc->SetAction(Action);
		}
		else if (IdleAreas.Num() > 0) //fallback for single object - goto idle area
		{
			MyNpc->SetTarget(IdleAreas[0]);
			MyNpc->SetAction("Idle");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "You've made the AI very angry. Watch your back!");
		}
	}
}

