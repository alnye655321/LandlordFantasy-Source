// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rooms/Room.h"
#include "Apartment.generated.h"

UCLASS()
class LANDLORDFANTASY_API AApartment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApartment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* ApartmentBoxRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* ApartmentCollisionBox;

	// called when player enters the box
	UFUNCTION()
		void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//gets all possible rooms, send to npc, which then goes to AI
	void SendToRoom(AActor * OtherActor);

	// called when player leaves the box
	UFUNCTION()
		void OnPlayerLeavePickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	TArray <AActor*> RoomsInApartment;
};
