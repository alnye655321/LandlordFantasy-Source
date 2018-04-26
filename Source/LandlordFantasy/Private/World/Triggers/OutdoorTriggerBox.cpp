// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NPCs/Npc.h"
#include "OutdoorTriggerBox.h"

AOutdoorTriggerBox::AOutdoorTriggerBox()
{

	PrimaryActorTick.bCanEverTick = true;

	OutdoorTriggerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("OutdoorTriggerRoot")); // initialize a component
	RootComponent = OutdoorTriggerRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(OutdoorTriggerRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

}

void AOutdoorTriggerBox::BeginPlay()
{
	LocationVec = GetActorLocation();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "my log2");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AOutdoorTriggerBox::OnPlayerEnterPickupBox); // on the overlap

}

// Called every frame
void AOutdoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// triggers head for indoor location in npc character
void AOutdoorTriggerBox::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "collision log2");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetName());
	ANpc* PossibleNpc = Cast<ANpc>(OtherActor);

	if (PossibleNpc != NULL)
	{
		PossibleNpc->setIsInside(true);

	}


}
