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

	NeedsMap.Add(TEXT("Bored"), 100);
	NeedsMap.Add(TEXT("Hungry"), 0);
	NeedsMap.Add(TEXT("Sleepy"), 100);
	NeedsMap.Add(TEXT("Tired"), 100);
	

}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();

	ANpcAI* AIController = Cast<ANpcAI>(GetController());

	//find a room entry point target
	FString EntryRoomTarget = "None"; //find a room to begin play
	AIController->SetDesiredRoomKey(EntryRoomTarget);

	//in behavior tree setting room to none means not in any room
	FString NoRoom = "None";
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

void ANpc::SetAIFindRoom(FString NewStringCondition)
{	
	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetFindRoom(NewStringCondition);
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

FVector ANpc::AnimPositionVector(AActor* MyTargetActor, float ForwardOffset, float RightOffset, float UpOffset)
{
	TargetActor = MyTargetActor;

	FVector MyTargetLoc = TargetActor->GetActorLocation();
	FVector MyTargetForward = TargetActor->GetActorForwardVector();
	FVector MyTargetRight = TargetActor->GetActorRightVector();
	FVector MyTargetUp = TargetActor->GetActorUpVector();

	FVector MyTargetMult = UKismetMathLibrary::Multiply_VectorFloat(MyTargetForward, ForwardOffset);
	FVector MyTargetMult2 = UKismetMathLibrary::Multiply_VectorFloat(MyTargetRight, RightOffset);
	FVector MyTargetMult3 = UKismetMathLibrary::Multiply_VectorFloat(MyTargetUp, UpOffset);

	FVector CombinedVector = UKismetMathLibrary::Add_VectorVector(MyTargetLoc, MyTargetMult);
	FVector CombinedVector2 = UKismetMathLibrary::Add_VectorVector(CombinedVector, MyTargetMult2);
	FVector CombinedVector3 = UKismetMathLibrary::Add_VectorVector(CombinedVector2, MyTargetMult3);

	FTransform VectorTransform = UKismetMathLibrary::Conv_VectorToTransform(CombinedVector3);

	return VectorTransform.GetLocation();

}

FRotator ANpc::AnimPositionRotator(AActor * MyTargetActor, float OffsetRoll, float OffsetPitch, float OffsetYaw)
{
	FVector TargetVector = MyTargetActor->GetActorForwardVector();
	//FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(TargetVector);

	FVector MyTargetForward = MyTargetActor->GetActorForwardVector();
	FVector MyTargetRight = MyTargetActor->GetActorRightVector();
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromXY(MyTargetForward, MyTargetRight);


	TargetRotation.Roll += OffsetRoll;
	TargetRotation.Pitch += OffsetPitch;
	TargetRotation.Yaw += OffsetYaw;

	return TargetRotation;
}

//called when entering apartment
void ANpc::ChooseRoomDestination(TArray <AActor*> RoomsInApartment)
{
	ANpcAI* AIController = Cast<ANpcAI>(GetController());

	AIController->DesiredRoom(NeedsMap, RoomsInApartment);

}

void ANpc::SetRoom(FString Room)
{

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetCurrentRoom(Room);
}

void ANpc::SetDesiredRoom(FString Room)
{

	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	AIController->SetDesiredRoomKey(Room);
}

FString ANpc::GetDesiredRoom()
{
	ANpcAI* AIController = Cast<ANpcAI>(GetController()); // update AI which sets BlackBoard key
	FString DesiredRoomKey = AIController->GetDesiredRoomKey();
	return DesiredRoomKey;
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



