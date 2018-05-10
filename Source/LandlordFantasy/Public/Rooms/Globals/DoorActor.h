// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rooms/IndoorTriggerBox.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class LANDLORDFANTASY_API ADoorActor : public AIndoorTriggerBox
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:

	UFUNCTION(BlueprintCallable, Category = "Doors")
	FVector GetXSpotLocation();

	UFUNCTION(BlueprintCallable, Category = "Doors")
	void SetXSpotLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Doors")
	FRotator GetXSpotRotation();

	UFUNCTION(BlueprintCallable, Category = "Doors")
	void SetXSpotRotation(FRotator NewRotation);



private:

	FVector XSpotLocation;
	FRotator XSpotRotation;
	
	
	
};
