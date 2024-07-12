// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mCapsule);
	mMesh->SetupAttachment(mCapsule);

	mCapsule->SetCapsuleHalfHeight(95.f);
	mCapsule->SetCapsuleRadius(35.f);
	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	mMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	AutoPossessAI = EAutoPossessAI::Disabled;
}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASelectPawn::OnMouse(bool Overlap)
{

}

