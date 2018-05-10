// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "ApartmentDoor.h"
#include "NPCs/Npc.h"
#include "NPCs/Characters/Lucy.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "Kismet/KismetMathLibrary.h"
#include "Globals/DoorActor.h"
#include <string>


// Sets default values
AApartmentDoor::AApartmentDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/GR_Stylized_Female_01/Character/Animations/Curves/CurveQuick"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

	//door open
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve2(TEXT("/Game/Rooms/Globals/Curves/Curve3Sec"));
	check(Curve2.Succeeded());

	FloatCurve2 = Curve2.Object;




}



// Called when the game starts or when spawned
void AApartmentDoor::BeginPlay()
{

	Super::BeginPlay();





}

// Called every frame
void AApartmentDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayNPCPostionComp != NULL)
	{
		PlayNPCPostionComp->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	//door opening
	if (PlayWalkThruDoorComp != NULL)
	{
		PlayWalkThruDoorComp->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
	
}

//character positioning
void AApartmentDoor::PlayNPCPostionCallback(float interpolatedVal)
{
	//set actor rotation based on curve
	FRotator NewRotation = FMath::Lerp(ActorInitialRotation, TargetRotation, interpolatedVal);

	FVector NewLocation = FMath::Lerp(ActorInitialLocation, TargetLocation, interpolatedVal);


	if (MyNpc != NULL)
	{
		MyNpc->SetActorRotation(NewRotation);
		MyNpc->SetActorLocation(NewLocation);
	}

}

void AApartmentDoor::PlayNPCPostionFinished()
{
	PlayNPCPostionComp->UnregisterComponent();
	PlayNPCPostionComp = NULL;
	ALucy* MyLucy = Cast<ALucy>(MyNpc);

	if (MyLucy != NULL)
	{
		MyLucy->DoorPosition(MyDoorActor);
	}

}

void AApartmentDoor::PlayNPCPostion(ANpc * Npc, ADoorActor * Door)
{
	MyNpc = Npc;
	MyDoorActor = Door;



	//timeline curve - door opening
	FOnTimelineFloat PlayNPCPostionCallback;
	FOnTimelineEventStatic PlayNPCPostionFinished;

	//timeline curve - character door positioning
	PlayNPCPostionComp = this->SetUpTimeline("PlayNPCPostionCallback", PlayNPCPostionCallback, "PlayNPCPostionFinished", PlayNPCPostionFinished, 5.0f);
	PlayNPCPostionComp->AddInterpFloat(FloatCurve, PlayNPCPostionCallback);
	PlayNPCPostionComp->RegisterComponent();
	

	this->NPCAnimationStopMovement(Npc);
	MyDoorActor->SetActorEnableCollision(false);

	ActorInitialRotation = MyNpc->GetActorRotation();
	ActorInitialLocation = MyNpc->GetActorLocation();


	if (PlayNPCPostionComp != NULL && Npc != NULL && MyDoorActor != NULL)
	{
		TargetRotation = Npc->AnimPositionRotator(MyDoorActor, 0.0f, 0.0f, -90.0f);

		TargetLocation = Npc->AnimPositionVector(MyDoorActor, -30.0f, 80.0f, 0.0f);

		PlayNPCPostionComp->PlayFromStart();
	}
}


//door opening
void AApartmentDoor::PlayWalkThruDoorCallback(float interpolatedVal)
{
	//set actor rotation based on curve
	//FRotator NewRotation = FMath::Lerp(ActorInitialRotation, TargetRotation, interpolatedVal);

	FVector NewLocation = FMath::Lerp(ActorInitialLocation, TargetLocation, interpolatedVal);

	if (MyNpc != NULL)
	{
		//MyDoorActor->SetActorRotation(NewRotation);
		MyNpc->SetActorLocation(NewLocation);
	}

}

void AApartmentDoor::PlayWalkThruDoorFinished()
{
	PlayWalkThruDoorComp->UnregisterComponent();
	PlayWalkThruDoorComp = NULL;

	ALucy* MyLucy = Cast<ALucy>(MyNpc);

	if (MyLucy != NULL)
	{
		MyLucy->WalkThruDoor();
	}

}

void AApartmentDoor::PlayWalkThruDoor(ANpc * Npc, ADoorActor * Door)
{
	MyNpc = Npc;
	MyDoorActor = Door;



	//timeline curve - walk thru opening
	FOnTimelineFloat PlayWalkThruDoorCallback;
	FOnTimelineEventStatic PlayWalkThruDoorFinished;

	//timeline curve - door opening
	PlayWalkThruDoorComp = this->SetUpTimeline("PlayWalkThruDoorCallback", PlayWalkThruDoorCallback, "PlayWalkThruDoorFinished", PlayWalkThruDoorFinished, 5.0f);
	PlayWalkThruDoorComp->AddInterpFloat(FloatCurve2, PlayWalkThruDoorCallback);
	PlayWalkThruDoorComp->RegisterComponent();

	this->NPCAnimationStopMovement(Npc);
	MyDoorActor->SetActorEnableCollision(false);

	ActorInitialRotation = MyNpc->GetActorRotation();
	ActorInitialLocation = MyNpc->GetActorLocation();


	if (PlayWalkThruDoorComp != NULL && Npc != NULL && MyDoorActor != NULL)
	{
		//TargetRotation = Npc->AnimPositionRotator(MyDoorActor, 0.0f, 0.0f, 0.0f);

		TargetLocation = Npc->AnimPositionVector(MyDoorActor, 20.0f, -150.0f, 0.0f);

		PlayWalkThruDoorComp->PlayFromStart();
	}
}








