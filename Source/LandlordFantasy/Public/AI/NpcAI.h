// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "NPCs/Npc.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Triggers/OutdoorTriggerBox.h"
#include "Rooms/IndoorTriggerBox.h"
#include "NpcAI.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class ANpcAI : public AAIController
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

	FVector LocationVec;
	int32 randEntry; // for choosing entrance to building

	ANpc* ControlledNpc;

public:

	virtual void Possess(class APawn *InPawn) override;

	void SetOutdoorBox(class AOutdoorTriggerBox* InActor);

	void SetTarget(AActor * InActor);

	UObject* GetTarget();

	void SetTargetVector(FVector location);

	class AOutdoorTriggerBox* GetOutdoorBox() const;

	void SetIndoorBox(AIndoorTriggerBox * InActor);

	AIndoorTriggerBox * GetIndoorBox() const;

	AActor* GetNearestActor(TArray<AActor*> FoundActors);

	void setIsInside(bool inside);

	void SetIsInBedroom(bool bedroom);

	void SetIsInteracting(bool interacting);

	int32 getRandOutdoorEntry(); // set random int for picking from entry box array at the moment
	void setRandOutdoorEntry(int32 setInt);

	UFUNCTION(BlueprintCallable, Category = "LandlordAI")
		FVector getLocationVec();

	UFUNCTION(BlueprintCallable, Category = "LandlordAI")
		void setLocationVec(FVector location);

protected:

	//Blackboard Keys
	int32 Target;
	int32 TargetVector;
	int32 OutdoorBoxID;
	int32 IndoorBoxID;
	int32 SelfActor;
	int32 IsInside;
	int32 IsInBedroom;
	int32 IsInteracting;



public:
	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	
	
	
	
};
