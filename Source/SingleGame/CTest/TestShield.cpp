// Fill out your copyright notice in the Description page of Project Settings.


#include "TestShield.h"

// Sets default values
ATestShield::ATestShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/TestShieldMesh.TestShieldMesh'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	mMesh->SetRelativeScale3D(FVector(0.1f, 0.75f, 0.75f)); 
	// 카메라 충돌 무시
	mMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, 
		ECollisionResponse::ECR_Ignore);

	SetLifeSpan(3.f);
}

// Called when the game starts or when spawned
void ATestShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

