// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "BTTask_PickRoom.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/NpcAI.h"
#include "NPCs/Npc.h"
#include "Rooms/Apartment.h"


UBTTask_PickRoom::UBTTask_PickRoom(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_PickRoom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpcAI* MyController = Cast<ANpcAI>(OwnerComp.GetAIOwner());
	UObject* MyActor = MyController->GetSelf();
	ANpc* PossibleNpc = Cast<ANpc>(MyActor);

	if (MyController != NULL && PossibleNpc != NULL)
	{
		TArray <AActor*> Overlapping;
		PossibleNpc->GetOverlappingActors(Overlapping); //get all rooms in this apartment

		//look for apartment
		for (auto Overlap : Overlapping)
		{
			AApartment* PossibleApartment = Cast<AApartment>(Overlap);
			if (PossibleApartment != NULL)
			{
				PossibleApartment->SendToRoom(PossibleNpc); //goes back to ai to determine action based on needs
			}
		}

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed; // if no TriggerActors it is failure
	}

}

