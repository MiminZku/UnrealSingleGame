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
