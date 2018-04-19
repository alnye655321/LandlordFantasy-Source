// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "LandlordVRCharacter.h"


ALandlordVRCharacter::ALandlordVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default


}

void ALandlordVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function 
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");
}

void ALandlordVRCharacter::myTestCall_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "me test");
}



