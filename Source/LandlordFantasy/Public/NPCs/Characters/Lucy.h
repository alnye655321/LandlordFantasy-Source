// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCs/Npc.h"
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


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Curves
	UPROPERTY()
		UTimelineComponent* MyTimeline;

	UPROPERTY()
		UCurveFloat* FloatCurve;

	UFUNCTION()
		void TimelineCallback(float interpolatedVal);

	UFUNCTION()
		void TimelineFinishedCallback();

	void PlayTimeline();

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

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
