// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mCapsule);

	mMesh->SetupAttachment(mCapsule);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mDeathDelegate.IsBound())	// 등록된 함수가 있을 경우
		mDeathDelegate.Broadcast();	// 그 등록된 함수를 실행
}

float AAIPawn::TakeDamage(float DamageAmount, 
	FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Destroy();


	return DamageAmount;
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}