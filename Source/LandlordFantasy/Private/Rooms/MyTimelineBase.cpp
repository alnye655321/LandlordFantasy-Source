// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include <string>
#include "NPCs/Npc.h"
#include "MyTimelineBase.h"


// Sets default values
AMyTimelineBase::AMyTimelineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimelineRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TimelineRoot")); // initialize a component
	RootComponent = TimelineRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->bGenerateOverlapEvents = true; // set overlap events to true	
	CollisionBox->AttachToComponent(TimelineRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

}

// Called when the game starts or when spawned
void AMyTimelineBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UTimelineComponent* AMyTimelineBase::SetUpTimeline(std::string CallBackFuncName, FOnTimelineFloat &onTimelineCallback, std::string FinishedFuncName, FOnTimelineEventStatic &onTimelineFinishedCallback, float TimeLength)
{
	//timeline
	MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
	MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
	this->BlueprintCreatedComponents.Add(MyTimeline); // add to array so it gets saved
	MyTimeline->SetNetAddressable();	// component has a stable name that can be referenced for replication

	MyTimeline->SetPropertySetObject(this); // set which object the timeline should drive properties on
	MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

	MyTimeline->SetLooping(false);
	MyTimeline->SetTimelineLength(TimeLength);
	MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	MyTimeline->SetPlaybackPosition(0.0f, false);

	//add the float curve to the timeline and connect to timeline interpolation function
	onTimelineCallback.BindUFunction(this, FName{ *FString(CallBackFuncName.c_str()) });//bind delegate
	onTimelineFinishedCallback.BindUFunction(this, FName{ *FString(FinishedFuncName.c_str()) });
	//MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
	MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

	//MyTimeline->RegisterComponent();

	return MyTimeline;
}




void AMyTimelineBase::NPCAnimationStopMovement(ANpc* Npc)
{
	ActorInitialRotation = Npc->GetActorRotation();
	ActorInitialLocation = Npc->GetActorLocation();

	if (Npc != NULL)
	{
		Npc->SetIsWalking(false); //disable walking before animation
		Npc->SetIsInteracting(true);
		Npc->SetActorEnableCollision(false);
		Npc->GetCharacterMovement()->SetMovementMode(MOVE_None);//disable movement before animation	
	}

}

