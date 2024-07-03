// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "MonsterMovement.h"
#include "MonsterController.h"

AMonsterPawn::AMonsterPawn()
{
	mMovement = CreateDefaultSubobject<UMonsterMovement>(TEXT("Movement"));

	mMovement->SetUpdatedComponent(RootComponent);

	mCapsule->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterController::StaticClass();
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
	//	FString::Printf(TEXT("MonsterPawn Team ID : %d"), mTeamID));

	AMonsterController* MonsterController = Cast<AMonsterController>(NewController);
	if (IsValid(MonsterController))
		MonsterController->SetTeamId(mTeamID);
}

void AMonsterPawn::SetState(EAIState State)
{
	Super::SetState(State);
}
