// Fill out your copyright notice in the Description page of Project Settings.

#include "LandlordFantasy.h"
#include "AI/NpcAI.h"
#include "World/Triggers/OutdoorTriggerBox.h"
#include "Kismet/KismetMathLibrary.h"
#include "Npc.h"


// Sets default values
ANpc::ANpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();

	ANpcAI* AIController = Cast<ANpcAI>(GetController());

	//in behavior tree setting room to none means move to a new room
	FString NoRoom = "None"; //find a room to begin play
	SetRoom(NoRoom);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOutdoorTriggerBox::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		int32 randIndex = AIController->getRandOutdoorEntry();
		AActor* Actor = FoundActors[randIndex];
		AOutdoorTriggerBox* outdoorTriggerBox = Cast<AOutdoorTriggerBox>(Actor);
		//AIController->SetWaypoint(outdoorTriggerBox);

	}

	isWalking = true;
	IsInteracting = false;
	isInside = false; // !!! have a check, all npcs may not start outside
	
}

// Called every frame
void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// getters & setters
void ANpc::SetTarget(AActor * InActor)
{
	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetTarget(InActor);
}

void ANpc::SetTargetVector(FVector TargetVec)
{
	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetTargetVector(TargetVec);
}

bool ANpc::GetIsWalking()
{
	return isWalking;
}

void ANpc::SetIsWalking(bool WalkingCondition)
{
	isWalking = WalkingCondition;
}

bool ANpc::GetIsIsInteracting()
{
	return IsInteracting;
}

void ANpc::SetIsInteracting(bool IsInteractingCondition)
{
	IsInteracting = IsInteractingCondition;

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetIsInteracting(IsInteractingCondition);
}

bool ANpc::getIsInside()
{
	return isInside;
}

void ANpc::setIsInside(bool inside)
{
	isInside = inside; // update local npc

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->setIsInside(inside);
}

void ANpc::SetRoom(FString Room)
{

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetCurrentRoom(Room);
}

void ANpc::SetAction(FString Action)
{

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetCurrentAction(Action);
}

void ANpc::facePlayer()
{
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerChar != NULL)
	{
		FVector PlayerLocation = PlayerChar->GetActorLocation();
		FVector NpcLocation = this->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(NpcLocation, PlayerLocation);
		LookAtRotation.Pitch = LookAtRotation.Pitch + 20.0f; // increase pitch to look at player
		this->SetActorRotation(LookAtRotation); // set rotation
	}

}

