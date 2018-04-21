// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rooms/IdleArea.h"
#include "BedRoomIdleArea.generated.h"

UCLASS()
class LANDLORDFANTASY_API ABedRoomIdleArea : public AIdleArea
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABedRoomIdleArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
