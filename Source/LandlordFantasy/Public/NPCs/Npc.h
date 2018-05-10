// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Npc.generated.h"

UCLASS()
class LANDLORDFANTASY_API ANpc : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpc();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree *BotBehavior;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool isWalking;
	bool IsInteracting;
	bool isInside;

	UFUNCTION(BlueprintCallable, Category = "LandlordAI")
		void facePlayer();

	// getters & setters

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void SetTarget(class AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void SetTargetVector(FVector TargetVec);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		bool GetIsWalking();

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void SetIsWalking(bool WalkingCondition);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		bool GetIsIsInteracting();

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void SetIsInteracting(bool IsInteractingCondition);

	void SetAIFindRoom(FString NewStringCondition);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		bool getIsInside();

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		void setIsInside(bool outside);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		FVector AnimPositionVector(AActor* MyTargetActor, float ForwardOffset, float RightOffset, float UpOffset);

	UFUNCTION(BlueprintCallable, Category = "LandlordNPC")
		FRotator AnimPositionRotator(AActor* MyTargetActor, float OffsetRoll, float OffsetPitch, float OffsetYaw);

	void ChooseRoomDestination(TArray <AActor*> RoomsInApartment);

	void SetRoom(FString Room);

	void SetDesiredRoom(FString Room);

	FString GetDesiredRoom();

	void SetAction(FString Action);


private:
	AActor * TargetActor;

	TMap<FString, int32> NeedsMap;
	
	
};
