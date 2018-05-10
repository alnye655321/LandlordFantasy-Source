// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Rooms/BedRoom/Utilities/BedTimeline.h"
#include "NPCs/Npc.h"
#include "NPCs/Characters/Lucy.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "Kismet/KismetMathLibrary.h"
#include <string>


// Sets default values
ABedTimeline::ABedTimeline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/GR_Stylized_Female_01/Character/Animations/Curves/CurveQuick"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;




}

// Called when the game starts or when spawned
void ABedTimeline::BeginPlay()
{
	FOnTimelineFloat BedTimelineCallback;
	FOnTimelineEventStatic BedTimelineFinishedCallback;

	Super::BeginPlay();

	//timeline curve	
	BedTimelineComp = this->SetUpTimeline("TimelineCallback", BedTimelineCallback, "TimelineFinishedCallback", BedTimelineFinishedCallback, 5.0f);
	BedTimelineComp->AddInterpFloat(FloatCurve, BedTimelineCallback);
	BedTimelineComp->RegisterComponent();

	
	
}

// Called every frame
void ABedTimeline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BedTimelineComp != NULL)
	{
		BedTimelineComp->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

}


void ABedTimeline::TimelineCallback(float interpolatedVal)
{
	//set actor rotation based on curve
	FRotator NewRotation = FMath::Lerp(ActorInitialRotation, TargetRotation, interpolatedVal); //npc and bed

	//set actor location based on curve
	FVector NewLocation = FMath::Lerp(ActorInitialLocation, TargetLocation, interpolatedVal);

	if (MyNpc != NULL)
	{
		MyNpc->SetActorRotation(NewRotation);
		MyNpc->SetActorLocation(NewLocation);
	}

}


void ABedTimeline::TimelineFinishedCallback()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "timeline finished");
	ALucy* MyLucy = Cast<ALucy>(MyNpc);

	if (MyLucy != NULL)
	{
		MyLucy->TriggerLayOnBedAnim(MyBed);
	}	

}


void ABedTimeline::PlayTimeline(ANpc* Npc, ABed* Bed)
{
	MyNpc = Npc;
	MyBed = Bed;

	this->NPCAnimationStopMovement(Npc);
	MyBed->SetActorEnableCollision(false);


	if (BedTimelineComp != NULL && Npc != NULL && Bed != NULL)
	{
		//rotation based on orientation of bed
		BedRightVector = Bed->GetActorRightVector();
		TargetRotation = UKismetMathLibrary::MakeRotFromX(BedRightVector);
		TargetRotation.Yaw += 45.0f;

		//location from static mesh marker in bed
		TargetLocation = Bed->GetXSpotLocation();
		TargetLocation.Z += 100.0f; //adjust npc to a new height to fit on bed
		TargetLocation.X += 20.0f;

		BedTimelineComp->PlayFromStart();
	}

}





