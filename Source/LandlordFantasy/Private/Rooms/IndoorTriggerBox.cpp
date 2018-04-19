// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "IndoorTriggerBox.h"


// Sets default values
AIndoorTriggerBox::AIndoorTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IndoorTriggerBoxRoot = CreateDefaultSubobject<USceneComponent>(TEXT("IndoorTriggerBox")); // initialize a component
	RootComponent = IndoorTriggerBoxRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(IndoorTriggerBoxRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void AIndoorTriggerBox::BeginPlay()
{
	//Super::BeginPlay();

	LocationVec = GetActorLocation();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AIndoorTriggerBox::OnPlayerEnterPickupBox); // on the overlap
	
}

// Called every frame
void AIndoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AIndoorTriggerBox::getLocationVec()
{
	return LocationVec;
}

// triggers present in indoor location for npc character
void AIndoorTriggerBox::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "collision log2");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName());
	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		//PossibleNpc->setIsOutside(false); // inside now
	}


}

