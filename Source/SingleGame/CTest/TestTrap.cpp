// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTrap.h"
#include "MyCharacter.h"

// Sets default values
ATestTrap::ATestTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	static ConstructorHelpers::FClassFinder<AActor>
		TestTrap(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestTrap.BP_TestTrap_C'"));
	if (TestTrap.Succeeded())
	{
		mTestTrap = TestTrap.Class;
	}

	SetRootComponent(mBoxCollision);

	mBoxCollision->SetCollisionProfileName(TEXT("Item"));
	mBoxCollision->SetBoxExtent(FVector(100.f, 100.f, 50.f));
}

// Called when the game starts or when spawned
void ATestTrap::BeginPlay()
{
	Super::BeginPlay();

	mBoxCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ATestTrap::CollisionBeginOverlap);
}

// Called every frame
void ATestTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestTrap::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		SpawnTrap();
	}
}

void ATestTrap::SpawnTrap()
{
	UE_LOG(Sac6, Warning, TEXT("Spawn Trap"));
	GetWorld()->SpawnActor<AActor>(
		mTestTrap,
		GetActorLocation() + GetActorUpVector() * 500, FRotator(180, 0, 0));
}