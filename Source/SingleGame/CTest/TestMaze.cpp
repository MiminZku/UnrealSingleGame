// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMaze.h"
#include "TestItem.h"

// Sets default values
ATestMaze::ATestMaze()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mExitDoor = nullptr;

	static ConstructorHelpers::FClassFinder<AActor>
		TestWall(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestWall.BP_TestWall_C'"));
	if (TestWall.Succeeded())
	{
		mWall = TestWall.Class;
	}

	mMaze.Init(mMazeLen * mMazeLen, 0);
}

// Called when the game starts or when spawned
void ATestMaze::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black,
			FString::Printf(TEXT("Item left : %d"), mItemNum));
	}

	//SpawnItem();

	//mExitDoor = GetWorld()->SpawnActor<ATestDoor>(
	//	ATestDoor::StaticClass(),
	//	GetActorLocation() + FVector(2000.f, 0.f, 262.5f),
	//	FRotator::ZeroRotator);
	//mExitDoor->DisableCollision();
	//mExitDoor->SetActorScale3D(FVector(1.f, 1.9f, 1.75f));
}

// Called every frame
void ATestMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestMaze::GenerateMaze()
{

}

void ATestMaze::SpawnItem()
{
	ATestItem* TestItem;
	for (int32 i = 0; i <= mItemNum; ++i)
	{
		if (i == mItemNum)
		{
			mExitDoor = GetWorld()->SpawnActor<ATestDoor>(
				ATestDoor::StaticClass(),
				GetActorLocation() + FVector(i * 500.f, 0.f, 262.5f),
				FRotator::ZeroRotator);
			mExitDoor->DisableCollision();
			mExitDoor->SetActorScale3D(FVector(1.f, 1.9f, 1.75f));
			break;
		}
		TestItem = GetWorld()->SpawnActor<ATestItem>(
			ATestItem::StaticClass(),
			GetActorLocation() + FVector(i * 500, 0, 50),
			FRotator::ZeroRotator);
		TestItem->SetMaze(this);
	}
}

void ATestMaze::DecreaseItem()
{
	--mItemNum;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black,
			FString::Printf(TEXT("Item left : %d"), mItemNum));
	}

	if (0 == mItemNum)
	{
		mExitDoor->OpenDoor();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
				FString::Printf(TEXT("Door Opened!")));
		}
	}
}

