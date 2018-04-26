// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OutdoorTriggerBox.generated.h"

UCLASS()
class LANDLORDFANTASY_API AOutdoorTriggerBox : public AActor
{
	GENERATED_BODY()

public:
	AOutdoorTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* OutdoorTriggerRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;


	// called when player enters the box
	UFUNCTION()
		void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



private:

	FVector LocationVec;

	
};
