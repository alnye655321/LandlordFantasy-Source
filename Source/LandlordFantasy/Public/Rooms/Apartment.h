// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	
	
};
