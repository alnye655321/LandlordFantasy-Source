// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindKitchenAction.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_FindKitchenAction : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
	
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; // run the task on node and return
	
	
};
