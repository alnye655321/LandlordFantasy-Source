// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCs/Npc.h"
#include "Rooms/BedRoom/Items/Bed.h"
#include "BedTimeline.generated.h"

UCLASS()
class LANDLORDFANTASY_API ABedTimeline : public AActor
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

	//Curves
	UPROPERTY()
		UTimelineComponent* MyTimeline;

	UPROPERTY()
		UCurveFloat* FloatCurve;

	UFUNCTION()
		void TimelineCallback(float interpolatedVal);

	UFUNCTION()
		void TimelineFinishedCallback();

	void AnimationMovementSetup(ANpc* Npc);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* BedTimelineRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

private:
	ANpc* MyNpc;
	ABed* MyBed;


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
