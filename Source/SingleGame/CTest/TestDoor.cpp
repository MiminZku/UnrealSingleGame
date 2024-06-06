// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDoor.h"
#include "MyCharacter.h"

// Sets default values
ATestDoor::ATestDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Door.Door'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	SetRootComponent(mBoxCollision);
	mMesh->SetupAttachment(mBoxCollision);

	mMesh->SetWorldScale3D(FVector(0.2f, 2.f, 3.f));
	mMesh->SetRelativeLocation(FVector(0.f, 100.f, 0.f));

	mBoxCollision->SetCollisionProfileName(TEXT("Item"));
	mBoxCollision->SetBoxExtent(FVector(300.f, 100.f, 150.f));
}

// Called when the game starts or when spawned
void ATestDoor::BeginPlay()
{
	Super::BeginPlay();

	// Overlap 일 때
	mBoxCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ATestDoor::CollisionBeginOverlap);
	mBoxCollision->OnComponentEndOverlap.AddDynamic(this,
		&ATestDoor::CollisionEndOverlap);
}

// Called every frame
void ATestDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EDoorState::Opening == mState)
	{
		if (bDir)	// forward 방향으로 열릴 때
		{
			if (mMesh->GetRelativeRotation().Yaw < 90)
			{
				mMesh->AddRelativeRotation(FRotator(0, mRotateSpeed * DeltaTime, 0));
			}
			else
			{
				mMesh->SetRelativeRotation(FRotator(0, 90, 0));
				mState = EDoorState::Opened;
				UE_LOG(Sac6, Warning, TEXT("Door Opened"));
			}
		}
		else	// 반대 방향으로 열릴 때
		{
			if (mMesh->GetRelativeRotation().Yaw > -90)
			{
				mMesh->AddRelativeRotation(FRotator(0, -mRotateSpeed * DeltaTime, 0));
			}
			else
			{
				mMesh->SetRelativeRotation(FRotator(0, -90, 0));
				mState = EDoorState::Opened;
				UE_LOG(Sac6, Warning, TEXT("Door Opened"));
			}
		}
	}
	else if (EDoorState::Closing == mState)
	{
		if (mMesh->GetRelativeRotation().Yaw > 0)
		{
			mMesh->AddRelativeRotation(FRotator(0, -mRotateSpeed * DeltaTime, 0));
		}
		else if (mMesh->GetRelativeRotation().Yaw < 0)
		{
			mMesh->AddRelativeRotation(FRotator(0, mRotateSpeed * DeltaTime, 0));
		}
		else
		{
			mMesh->SetRelativeRotation(FRotator(0, 0, 0));
			mState = EDoorState::Closed;
			UE_LOG(Sac6, Warning, TEXT("Door Closed"));
		}
	}
}

void ATestDoor::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		FVector playerLoc = Player->GetActorLocation();	playerLoc.Z = 0;
		FVector doorLoc = GetActorLocation();			doorLoc.Z = 0;
		FVector vecToPlayer = playerLoc - doorLoc;
		double dot = FVector::DotProduct(vecToPlayer, GetActorForwardVector());
		bDir = (dot < 0) ? true : false;
		OpenDoor();
	}
}

void ATestDoor::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		CloseDoor();
	}
}

void ATestDoor::OpenDoor()
{
	//mMesh->AddRelativeRotation(FRotator(0, 90, 0));
	mState = EDoorState::Opening;
}

void ATestDoor::CloseDoor()
{
	//mMesh->AddRelativeRotation(FRotator(0, -90, 0));
	mState = EDoorState::Closing;
}

void ATestDoor::DisableCollision()
{
	mBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}