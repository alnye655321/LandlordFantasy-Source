// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "NpcAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NPCs/Npc.h"
#include "World/Triggers/OutdoorTriggerBox.h"
#include "Rooms/IndoorTriggerBox.h"
#include "Rooms/BedRoom/BedRoom.h"
#include "Rooms/Kitchen/Kitchen.h"


ANpcAI::ANpcAI(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;

	LocationVec = FVector(0.0f, 0.0f, 0.0f);

	// for setting the outdoor AI entry point to house
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOutdoorTriggerBox::StaticClass(), FoundActors);
	randEntry = FMath::RandRange(0, FoundActors.Num() - 1); // at the moment should be 0 or 1 for the 2 boxes in play !!! needs changing for more entry boxes
}

void ANpcAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	ANpc *Bot = Cast<ANpc>(InPawn);

	ControlledNpc = Bot;

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		// Define blackboard keys
		Target = BlackboardComp->GetKeyID("Target");
		TargetVector = BlackboardComp->GetKeyID("TargetVector");
		OutdoorBoxID = BlackboardComp->GetKeyID("OutdoorBox");
		IndoorBoxID = BlackboardComp->GetKeyID("IndoorBox");
		SelfActor = BlackboardComp->GetKeyID("SelfActor");
		IsInside = BlackboardComp->GetKeyID("IsInside");
		IsInteracting = BlackboardComp->GetKeyID("IsInteracting");
		DesiredRoomKey = BlackboardComp->GetKeyID("DesiredRoom");
		FindRoom = BlackboardComp->GetKeyID("FindRoom");

		BehaviorComp->StartTree(*(Bot->BotBehavior));

		if (BlackboardComp)
		{
			BlackboardComp->SetValue<UBlackboardKeyType_Object>(SelfActor, Bot); // add SelfObject ref in Blackboard to this NPC Bot
			BlackboardComp->SetValueAsString("FindRoom", TEXT("None"));
		}
	}
}


int32 ANpcAI::getRandOutdoorEntry()
{
	return randEntry;
}


void ANpcAI::setRandOutdoorEntry(int32 setInt)
{
	randEntry = setInt;
}


// should perform some additional validity check here !!!
FVector ANpcAI::getLocationVec()
{
	return LocationVec;
}


void ANpcAI::setLocationVec(FVector location)
{
	LocationVec = location;
}

void ANpcAI::setIsInside(bool inside)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(IsInside, inside);
	}
}

void ANpcAI::SetIsInteracting(bool interacting)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(IsInteracting, interacting);
	}
}

void ANpcAI::DesiredRoom(TMap<FString, int32> NeedsMap, TArray <AActor*> RoomsInApartment)
{
	FString NeedStr;

	FString BoredStr = TEXT("Bored");
	FString HungryStr = TEXT("Hungry");
	FString SleepyStr = TEXT("Sleepy");
	FString TiredStr = TEXT("Tired");

	NeedsMap.ValueSort([](const int32 A, const int32 B) {
		return A < B;  //sort needs by value
	});

	// could insert randomness here and handle same need values (equivalent values can come in any order)
	for (auto& Need : NeedsMap)
	{
		NeedStr = Need.Key;
		//int32 NeedLevel = Need.Value;

		break; //set up conditional here if needed

	}

	if (NeedStr == TEXT("Bored"))
	{
		for (auto RoomInApartment : RoomsInApartment)
		{
			ABedRoom* PossibleBedRoom = Cast<ABedRoom>(RoomInApartment);

			if (BlackboardComp)
			{
				//BlackboardComp->SetValue<UBlackboardKeyType_Object>(Target, PossibleBedRoom->GetXSpotLocation());
			}
		}
	}
	else if (NeedStr == TEXT("Hungry"))
	{
		for (auto RoomInApartment : RoomsInApartment)
		{
			AKitchen* PossibleKitchen = Cast<AKitchen>(RoomInApartment);

			if (BlackboardComp && PossibleKitchen)
			{
				AActor* XSpot = PossibleKitchen->GetXSpotLocation(); //colliding entry point actor
				BlackboardComp->SetValue<UBlackboardKeyType_Object>(Target, XSpot);
				SetDesiredRoomKey("Kitchen");
				break; //only one room target entry point at a time
			}
		}
	}
	else if (NeedStr == TEXT("Sleepy"))
	{
		for (auto RoomInApartment : RoomsInApartment)
		{
			ABedRoom* PossibleBedRoom = Cast<ABedRoom>(RoomInApartment);

			

			if (BlackboardComp && PossibleBedRoom)
			{
				AActor* XSpot = PossibleBedRoom->GetXSpotLocation();  //colliding entry point actor
				BlackboardComp->SetValue<UBlackboardKeyType_Object>(Target, XSpot);
				SetDesiredRoomKey("BedRoom");
				break; //only one room target entry point at a time
			}
		}
	}
	else if (NeedStr == TEXT("Tired"))
	{
		for (auto RoomInApartment : RoomsInApartment)
		{
			ABedRoom* PossibleBedRoom = Cast<ABedRoom>(RoomInApartment);

			if (BlackboardComp)
			{
				//BlackboardComp->SetValue<UBlackboardKeyType_Object>(Target, PossibleBedRoom->GetXSpotLocation());
			}
		}
	}

}

void ANpcAI::SetOutdoorBox(class AOutdoorTriggerBox* InActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(OutdoorBoxID, InActor);
		SetFocus(InActor);
	}
}

void ANpcAI::SetTarget(class AActor* InActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(Target, InActor);
	}
}

UObject* ANpcAI::GetTarget()
{
	//UObject* test = nullptr;
	if (BlackboardComp)
	{
		UObject *FoundObject = BlackboardComp->GetValue<UBlackboardKeyType_Object>(Target); //get blackboard value as object
		return FoundObject;
	}
	else
		return NULL;

}


UObject* ANpcAI::GetSelf()
{
	//UObject* test = nullptr;
	if (BlackboardComp)
	{
		UObject *FoundObject = BlackboardComp->GetValue<UBlackboardKeyType_Object>(SelfActor); //get blackboard value as object
		return FoundObject;
	}
	else
		return NULL;

}


void ANpcAI::SetCurrentRoom(FString InString)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString("CurrentRoom", InString);
	}
}

FString ANpcAI::GetCurrentRoom()
{
	if (BlackboardComp)
	{
		FString FoundString = BlackboardComp->GetValueAsString("CurrentRoom");
		return FoundString;
	}
	else
		return "";
}

void ANpcAI::SetFindRoom(FString InString)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString("FindRoom", InString);
	}
}

FString ANpcAI::GetFindRoom()
{
	if (BlackboardComp)
	{
		FString FoundString = BlackboardComp->GetValueAsString("FindRoom");
		return FoundString;
	}
	else
		return "";
}

void ANpcAI::SetDesiredRoomKey(FString InString)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString("DesiredRoom", InString);
	}
}

FString ANpcAI::GetDesiredRoomKey()
{
	if (BlackboardComp)
	{
		FString FoundString = BlackboardComp->GetValueAsString("DesiredRoom");
		return FoundString;
	}
	else
		return "";
}

void ANpcAI::SetCurrentAction(FString InString)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString("CurrentAction", InString);
	}
}

FString ANpcAI::GetCurrentAction()
{
	if (BlackboardComp)
	{
		FString FoundString = BlackboardComp->GetValueAsString("CurrentAction");
		return FoundString;
	}
	else
		return "";
}

void ANpcAI::SetTargetVector(FVector location)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Vector>(TargetVector, location);
	}
}


class AOutdoorTriggerBox* ANpcAI::GetOutdoorBox() const
{
	if (BlackboardComp)
	{
		return Cast<AOutdoorTriggerBox>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(OutdoorBoxID));
	}

	return NULL;
}

void ANpcAI::SetIndoorBox(class AIndoorTriggerBox* InActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(IndoorBoxID, InActor);
		SetFocus(InActor);
	}
}

class AIndoorTriggerBox* ANpcAI::GetIndoorBox() const
{
	if (BlackboardComp)
	{
		return Cast<AIndoorTriggerBox>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(IndoorBoxID));
	}

	return NULL;
}

AActor* ANpcAI::GetNearestActor(TArray<AActor*> FoundActors)
{
	//ANpc *Bot = Cast<ANpc>(InPawn);
	AActor* NpcActor = Cast<AActor>(ControlledNpc);

	float distance = 999999.0f;
	float newDistance = 0.0f;
	AActor* nearestActor = nullptr;

	for (AActor* actor : FoundActors)
	{
		newDistance = (NpcActor->GetActorLocation() - actor->GetActorLocation()).Size();
		if (newDistance < distance)
		{
			distance = newDistance;
			nearestActor = actor;
		}
	}
	return nearestActor;
}
