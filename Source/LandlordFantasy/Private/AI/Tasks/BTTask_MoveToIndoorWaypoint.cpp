// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "AI/Tasks/BTTask_MoveToIndoorWaypoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/NpcAI.h"
#include "NPCs/Npc.h"
#include "Rooms/IndoorTriggerBox.h"


UBTTask_MoveToIndoorWaypoint::UBTTask_MoveToIndoorWaypoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_MoveToIndoorWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpcAI* MyController = Cast<ANpcAI>(OwnerComp.GetAIOwner());

	// need to split up into multiple trigger box classes later (for different rooms etc.), or find way to target the one
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIndoorTriggerBox::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		int32 randIndex = FMath::RandRange(0, FoundActors.Num() - 1); // get random indoor trigger box to move toward
		AActor* Actor = FoundActors[randIndex];
		AIndoorTriggerBox* indoorBox = Cast<AIndoorTriggerBox>(Actor);
		MyController->SetIndoorBox(indoorBox);

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed; // if no TriggerActors it is failure
	}

}

