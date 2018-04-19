// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRCharacter.h"
#include "LandlordVRCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LANDLORDFANTASY_API ALandlordVRCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALandlordVRCharacter();

	// Tick is enabled
	virtual void Tick(float DeltaTime);

	// Blueprint callable test
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TestCppBP")
		void myTestCall();
	
	
	
	
};
