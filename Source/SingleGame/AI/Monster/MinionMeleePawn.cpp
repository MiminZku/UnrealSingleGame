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
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));
	if (HitAsset.Succeeded())
	{
		mAttackParticle = HitAsset.Object;
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

void AMinionMeleePawn::Attack()
{
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 200.f;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	TArray<FHitResult> hitResultArr;
	bool Collision = GetWorld()->SweepMultiByChannel(hitResultArr, Start, End,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(50.f), params);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Collision ? FColor::Orange : FColor::Blue;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f,
		100.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 1.f);
#endif

	if (Collision)
	{
		for (FHitResult& hitResult : hitResultArr)
		{
			FDamageEvent DmgEvent;
			hitResult.GetActor()->TakeDamage(10.f, DmgEvent, GetController(), this);
		}
	}
}
