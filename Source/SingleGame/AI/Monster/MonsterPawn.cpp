// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "MonsterMovement.h"
#include "MonsterController.h"
#include "MonsterDataManager.h"
#include "AIController.h"

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

	const FMonsterInfoData* Info = MonsterDataManager::GetInst()->FindInfo(mMonsterInfoKey);

	if (Info)
	{
		mAttack = Info->mAttack;
		mDefense = Info->mDefense;
		mLife = mLifeMax = Info->mLife;
		mMana = mManaMax = Info->mMana;
		mMoveSpeed = Info->mMoveSpeed;
		mAttackDistance = Info->mAttackDistance;
	}
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

void AMonsterPawn::Attack()
{
}

float AMonsterPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (mLife <= 0.f)
	{
		SetState(EAIState::Death);

		AAIController* Ctrl = GetController<AAIController>();

		if (IsValid(Ctrl))
		{
			//사유를 전달하며 비헤이비어 트리 종료
			Ctrl->GetBrainComponent()->StopLogic(TEXT("Death"));
		}
	}
	else
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		//	TEXT("Taked Damage"));
		mLife -= DamageAmount;
		SetState(EAIState::Hit);
	}


	return DamageAmount;
}
