// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAIPawn.h"

// Sets default values
ATestAIPawn::ATestAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetRootComponent(mCapsuleCollision);
	mMesh->SetupAttachment(mMesh);
	mMovement->SetUpdatedComponent(mCapsuleCollision);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	mCapsuleCollision->SetCapsuleHalfHeight(94.f);
	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -94.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void ATestAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ATestAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//
//}