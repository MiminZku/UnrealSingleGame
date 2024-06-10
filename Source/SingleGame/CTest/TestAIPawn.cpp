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
	mMesh->SetupAttachment(mCapsuleCollision);
	mMovement->SetUpdatedComponent(mCapsuleCollision);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Ranged_Dusk.Minion_Lane_Ranged_Dusk'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	mCapsuleCollision->SetCapsuleHalfHeight(85.f);
	mCapsuleCollision->SetCapsuleRadius(40.f);
	mCapsuleCollision->SetCollisionProfileName(TEXT("Monster"));

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -85.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

float ATestAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	// bCanBeDamaged가 false일 경우 0 반환, true일 경우 Damage 반환
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Damage : %.5f"), DamageAmount));

	mHP -= DamageAmount; 
	
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("HP : %.5f"), mHP));

	if (mHP <= 0.f)
	{
		Destroy();
	}

	return DamageAmount;;
}

// Called to bind functionality to input
//void ATestAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//
//}