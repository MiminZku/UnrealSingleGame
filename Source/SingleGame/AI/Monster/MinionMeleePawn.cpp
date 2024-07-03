// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionMeleePawn.h"
#include "MonsterDefaultAnimTemplate.h"

AMinionMeleePawn::AMinionMeleePawn()
{
	mCapsule->SetCapsuleHalfHeight(64.f);
	mCapsule->SetCapsuleRadius(30.f);

	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -64.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/White_Camp_Minion/Meshes/Minion_melee.Minion_melee'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		MinionABP(TEXT("/Script/Engine.AnimBlueprint'/Game/_AI/Monsters/MinionMelee/ABP_MinionMelee.ABP_MinionMelee_C'"));
	if (MinionABP.Succeeded())
	{
		mMesh->SetAnimInstanceClass(MinionABP.Class);
	}

}

void AMinionMeleePawn::BeginPlay()
{
	Super::BeginPlay();

	mMinionAnim = Cast<UMonsterDefaultAnimTemplate>(mMesh->GetAnimInstance());
}

void AMinionMeleePawn::SetState(EAIState State)
{
	Super::SetState(State);

	switch (State)
	{
	case EAIState::Idle:
		mMinionAnim->ChangeAnim(EMonsterDefaultAnim::Idle);
		break;
	case EAIState::Patrol:
		mMinionAnim->ChangeAnim(EMonsterDefaultAnim::Walk);
		break;
	case EAIState::Trace:
		mMinionAnim->ChangeAnim(EMonsterDefaultAnim::Run);
		break;
	case EAIState::Attack:
		mMinionAnim->ChangeAnim(EMonsterDefaultAnim::Attack);
		break;
	case EAIState::Death:
		mMinionAnim->ChangeAnim(EMonsterDefaultAnim::Death);
		break;
	default:
		break;
	}
}
