// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class LANDLORDFANTASY_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* XSpotLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Rooms")
		AActor* GetXSpotLocation();

	UFUNCTION(BlueprintCallable, Category = "Rooms")
		void SetXSpotLocation(AActor* NewLocation);
	
	
};
