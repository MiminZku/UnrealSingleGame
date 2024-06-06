// Fill out your copyright notice in the Description page of Project Settings.


#include "TestItem.h"
#include "TestGameMode.h"

// Sets default values
ATestItem::ATestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Cube.Cube'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mBody->SetCollisionProfileName(TEXT("Item"));

	mBody->SetBoxExtent(FVector(50.f, 50.f, 50.f));	// 모서리 절반 길이
}

// Called when the game starts or when spawned
void ATestItem::BeginPlay()
{
	Super::BeginPlay();
	
	// Block 일 때
	//mBody->OncomponentHit

	// Overlap 일 때
	mBody->OnComponentBeginOverlap.AddDynamic(this,
		&ATestItem::CollisionBeginOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this,
		&ATestItem::CollisionEndOverlap);
}

// Called every frame
void ATestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestItem::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(Sac6, Warning, TEXT("Begin Overlap"));

	ATestGameMode* GameMode = GetWorld()->GetAuthGameMode<ATestGameMode>();
	if (GameMode)
	{
		GameMode->AddScore(10);
	}

	Destroy();
}

void ATestItem::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(Sac6, Warning, TEXT("End Overlap"));

}

