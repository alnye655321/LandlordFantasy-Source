// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCs/Npc.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "Rooms/MyTimelineBase.h"
#include <string>
#include "BedTimeline.generated.h"

UCLASS()
class LANDLORDFANTASY_API ABedTimeline : public AMyTimelineBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABedTimeline();

	UFUNCTION(BlueprintCallable, Category = "Bed")
		void PlayTimeline(ANpc* Npc, ABed* Bed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		UCurveFloat* FloatCurve;
		
	UFUNCTION()
		void TimelineCallback(float interpolatedVal);

	UFUNCTION()
		void TimelineFinishedCallback();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	ANpc* MyNpc;
	ABed* MyBed;

	UTimelineComponent* BedTimelineComp;


	//initial rotation
	FRotator ActorInitialRotation;

	//target rotation
	FRotator TargetRotation;


	//initial location
	FVector ActorInitialLocation;

	//target location
	FVector TargetLocation;

	//target - right vector
	FVector BedRightVector;

	
	
};
