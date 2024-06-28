// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionMeleePawn.h"

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
}
