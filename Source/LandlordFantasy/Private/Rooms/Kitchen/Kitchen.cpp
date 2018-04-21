// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "Kitchen.h"

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
	LocationVec = GetActorLocation();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AKitchen::OnPlayerEnterPickupBox); // on the overlap

}

// Called every frame
void AKitchen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AKitchen::getLocationVec()
{
	return LocationVec;
}

// triggers in kitchen change in npc character
void AKitchen::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName() + "kitchen box");

	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
	}


}


