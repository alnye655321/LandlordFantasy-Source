// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rooms/MyTimelineBase.h"
#include "Globals/DoorActor.h"
#include "ApartmentDoor.generated.h"

/**
 * 
 */
UCLASS()
class LANDLORDFANTASY_API AApartmentDoor : public AMyTimelineBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AApartmentDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ApartmentDoor")
		void PlayNPCPostion(ANpc* Npc, ADoorActor* Door);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//chracter positioning infront of door
	UPROPERTY()
		UCurveFloat* FloatCurve;

	UFUNCTION()
		void PlayNPCPostionCallback(float interpolatedVal);

	UFUNCTION()
		void PlayNPCPostionFinished();


public:
	UFUNCTION(BlueprintCallable, Category = "ApartmentDoor")
		void PlayWalkThruDoor(ANpc* Npc, ADoorActor* Door);

protected:
	//chracter thru door
	UPROPERTY()
		UCurveFloat* FloatCurve2;

	UFUNCTION()
		void PlayWalkThruDoorCallback(float interpolatedVal);

	UFUNCTION()
		void PlayWalkThruDoorFinished();

private:
	ANpc * MyNpc;
	ADoorActor* MyDoorActor;

	UTimelineComponent* PlayNPCPostionComp;
	UTimelineComponent* PlayWalkThruDoorComp;

	//initial rotation
	FRotator ActorInitialRotation;

	//target rotation
	FRotator TargetRotation;


	//initial location
	FVector ActorInitialLocation;

	//target location
	FVector TargetLocation;


};
