// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "Rooms/BedRoom/Utilities/BedTimeline.h"
#include "NPCs/Npc.h"
#include "NPCs/Characters/Lucy.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABedTimeline::ABedTimeline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BedTimelineRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BedTimelineRoot")); // initialize a component
	RootComponent = BedTimelineRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(BedTimelineRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

	//get curve from editor for use as timeline
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/GR_Stylized_Female_01/Character/Animations/Curves/CurveQuick"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;


}

// Called when the game starts or when spawned
void ABedTimeline::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();

	//timeline curve
	if (FloatCurve != NULL)
	{
		//timeline
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
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });//bind delegate
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();

	}
	
}

// Called every frame
void ABedTimeline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
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

	AnimationMovementSetup(Npc);
	MyBed->SetActorEnableCollision(false);


	if (MyTimeline != NULL && Npc != NULL && Bed != NULL)
	{
		//rotation based on orientation of bed
		BedRightVector = Bed->GetActorRightVector();
		TargetRotation = UKismetMathLibrary::MakeRotFromX(BedRightVector);
		TargetRotation.Yaw += 45.0f;

		//location from static mesh marker in bed
		TargetLocation = Bed->GetXSpotLocation();
		TargetLocation.Z += 100.0f; //adjust npc to a new height to fit on bed
		TargetLocation.X += 20.0f;

		MyTimeline->PlayFromStart();
	}

}


void ABedTimeline::AnimationMovementSetup(ANpc* Npc)
{
	ActorInitialRotation = Npc->GetActorRotation();
	ActorInitialLocation = Npc->GetActorLocation();

	if (Npc != NULL)
	{
		Npc->SetIsWalking(false); //disable walking before animation
		Npc->SetIsInteracting(true);
		Npc->GetCharacterMovement()->SetMovementMode(MOVE_None);//disable movement before animation	
	}

}




