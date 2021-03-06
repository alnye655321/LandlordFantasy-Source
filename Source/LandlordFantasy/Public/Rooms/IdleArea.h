// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdleArea.generated.h"

UCLASS()
class LANDLORDFANTASY_API AIdleArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIdleArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* IdleRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

	// Static mesh for action trigger location
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* XSpot;

	// Static mesh for action trigger location
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Arrow;

	UFUNCTION(BlueprintCallable, Category = "Seats")
		FVector GetXSpotLocation();

	UFUNCTION(BlueprintCallable, Category = "Seats")
		void SetXSpotLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Seats")
		FRotator GetXSpotRotation();

	UFUNCTION(BlueprintCallable, Category = "Seats")
		void SetXSpotRotation(FRotator NewRotation);

	
private:

	FVector XSpotLocation;
	FRotator XSpotRotation;

	
	
};
