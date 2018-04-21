// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Lucy.h"
#include "AI/NpcAI.h"
#include "Rooms/Globals/Items/Seat.h"
#include "Kismet/KismetMathLibrary.h"
#include <string> 

// Sets default values
ALucy::ALucy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ANpcAI* AIController = Cast<ANpcAI>(GetController());//TODO not used yet

														 //get curve from editor for use as timeline
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/GR_Stylized_Female_01/Character/Animations/Curves/CurveQuick"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

}

void ALucy::BeginPlay()
{

	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();

	//timeline curve
	if (FloatCurve != NULL)
	{
		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(MyTimeline); // add to array so it gets saved
		MyTimeline->SetNetAddressable();	// component has a stable name that can be referenced for replication

		MyTimeline->SetPropertySetObject(this); // set which object the timeline should drive properties on
		MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		MyTimeline->SetLooping(false);
		MyTimeline->SetTimelineLength(5.0f);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MyTimeline->SetPlaybackPosition(0.0f, false);

		//add the float curve to the timeline and connect to timeline interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("SitOnChairTimelineCallback") });//bind delegate
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SitOnChairTimelineFinishedCallback") });
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();
		//PlayTimeline();
	}

}

void ALucy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "lucy debug msg");

	//timeline curve
	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

}


void ALucy::SitOnChairTimelineCallback(float interpolatedVal)
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(interpolatedVal));

	//set actor rotation based on curve
	FRotator NewRotation = FMath::Lerp(ActorInitialRotation, TargetRotation, interpolatedVal);

	//set actor location based on curve
	FVector NewLocation = FMath::Lerp(ActorInitialLocation, TargetLocation, interpolatedVal);

	SetActorRotation(NewRotation);
	SetActorLocation(NewLocation);
}

void ALucy::SitOnChairTimelineFinishedCallback()
{
	SitOnChair();
}

void ALucy::SitOnChairPlayTimeline()
{
	//get location and rotation of npc
	ActorInitialRotation = GetActorRotation();
	ActorInitialLocation = GetActorLocation();

	SetIsWalking(false); //disable walking before animation
	SetIsInteracting(true);
	GetCharacterMovement()->SetMovementMode(MOVE_None);//disable movement before animation	

	ANpcAI* AIController = Cast<ANpcAI>(GetController());
	ASeat* PossibleSeat = Cast<ASeat>(AIController->GetTarget()); //get a target from the AI which is a seat

	if (MyTimeline != NULL && PossibleSeat != NULL)
	{
		//rotation based on orientation of seat
		FVector SeatRightVector = PossibleSeat->GetActorRightVector();
		TargetRotation = UKismetMathLibrary::MakeRotFromX(SeatRightVector);		

		//location from static mesh marker in Seat
		TargetLocation = PossibleSeat->GetXSpotLocation();
		TargetLocation.Z += 50.0f; //adjust npc to a new height to fit on chair

		MyTimeline->PlayFromStart();
	}
}


