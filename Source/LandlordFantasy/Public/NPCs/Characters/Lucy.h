// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCs/Npc.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "Globals/DoorActor.h"
#include "Lucy.generated.h"

/**
*
*/
UCLASS()
class LANDLORDFANTASY_API ALucy : public ANpc
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALucy();

	// Tick is enabled
	virtual void Tick(float DeltaTime);

	void TriggerLayOnBedAnim(ABed* Bed);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DoorPosition_FromCpp"))
		void DoorPosition(ADoorActor* Door);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "WalkThruDoor_FromCpp"))
		void WalkThruDoor();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Curves
	UPROPERTY()
		UTimelineComponent* MyTimeline; //is actually SitTimline, started with this name :( good luck getting unreal to recognize a change!

	UPROPERTY()
		UCurveFloat* FloatCurve;

	UFUNCTION()
		void SitOnChairTimelineCallback(float interpolatedVal);

	UFUNCTION()
		void SitOnChairTimelineFinishedCallback();

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void SitOnChairPlayTimeline();

	void AnimationMovementSetup();


	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;


	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SitOnChair_FromCpp"))
		void SitOnChair();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LayOnBed_FromCpp"))
		void LayOnBed(ABed* Bed);


private:

	//initial rotation
	FRotator ActorInitialRotation;

	//target rotation
	FRotator TargetRotation;


	//initial location
	FVector ActorInitialLocation;

	//target location
	FVector TargetLocation;



};
