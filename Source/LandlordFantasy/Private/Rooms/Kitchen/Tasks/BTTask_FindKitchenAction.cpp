// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "BTTask_FindKitchenAction.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/NpcAI.h"
#include "NPCs/Npc.h"
#include "Rooms/Kitchen/Kitchen.h"


UBTTask_FindKitchenAction::UBTTask_FindKitchenAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_FindKitchenAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpcAI* MyController = Cast<ANpcAI>(OwnerComp.GetAIOwner());
	UObject* MyActor = MyController->GetSelf();
	ANpc* PossibleNpc = Cast<ANpc>(MyActor);

	if (MyController != NULL && PossibleNpc != NULL)
	{
		TArray <AActor*> Overlapping;
		PossibleNpc->GetOverlappingActors(Overlapping);


		for (auto Overlap : Overlapping)
		{
			AKitchen* PossibleKitchen = Cast<AKitchen>(Overlap);
			if (PossibleKitchen != NULL)
			{
				UObject* LastTargetObj = MyController->GetTarget();
				PossibleKitchen->KitchenInteract(PossibleNpc, LastTargetObj);
			}
		}

		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

}