// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rooms/Globals/Items/FurnitureItem.h"
#include "Bed.generated.h"

/**
 * 
 */
UCLASS()
class LANDLORDFANTASY_API ABed : public AFurnitureItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* BedRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

	UFUNCTION(BlueprintCallable, Category = "Beds")
		FVector GetXSpotLocation();

	UFUNCTION(BlueprintCallable, Category = "Beds")
		void SetXSpotLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Beds")
		FRotator GetXSpotRotation();

	UFUNCTION(BlueprintCallable, Category = "Beds")
		void SetXSpotRotation(FRotator NewRotation);

private:

	FVector XSpotLocation;
	FRotator XSpotRotation;
	
	
	
	
};
