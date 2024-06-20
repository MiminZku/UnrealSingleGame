// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"
#include "PlayerAnimInstance.h"

AKnightCharacter::AKnightCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -94.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/_Player/Knight/ABP_Knight.ABP_Knight_C'"));
	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	mAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

void AKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKnightCharacter::NormalAttack()
{
	mAnimInstance->PlayAttackMontage();
}