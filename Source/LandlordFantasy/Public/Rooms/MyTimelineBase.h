// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCs/Npc.h"
#include <string>
#include "MyTimelineBase.generated.h"

UCLASS()
class LANDLORDFANTASY_API AMyTimelineBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTimelineBase();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	//Curves
	UPROPERTY()
		UTimelineComponent* MyTimeline;


	UTimelineComponent* SetUpTimeline(std::string CallBackFuncName, FOnTimelineFloat &onTimelineCallback, std::string FinishedFuncName, FOnTimelineEventStatic &onTimelineFinishedCallback, float TimeLength);

	void NPCAnimationStopMovement(ANpc* Npc);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* TimelineRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

private:

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
