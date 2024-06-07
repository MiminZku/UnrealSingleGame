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
		TestWall(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_RandomMazeWall.BP_RandomMazeWall_C'"));
	if (TestWall.Succeeded())
	{
		mWall = TestWall.Class;
	}

	for (int i = 0; i < MAZE_LEN; ++i)
	{
		for (int j = 0; j < MAZE_LEN; ++j)
		{
			mMaze[i][j] = 1;
		}
	}
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

	mMaze[MAZE_LEN - 1][MAZE_LEN - 2] = 0;	// 출구
	GenerateMaze(1, 1, 0);	// 입구
	SelectItemLoc();
	SpawnMaze();
}

// Called every frame
void ATestMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestMaze::GenerateMaze(int32 x, int32 y, int32 dir)
{
	mMaze[x][y] = 0;
	mItemCoords.Add(x);
	mItemCoords.Add(y);
	if (0 == dir)    mMaze[x - 1][y] = 0;
	else if (1 == dir) mMaze[x][y - 1] = 0;
	else if (2 == dir) mMaze[x + 1][y] = 0;
	else if (3 == dir) mMaze[x][y + 1] = 0;

	int dirSeq[4] = { 0, 1, 2, 3 };
	for (int i = 0; i < 10; ++i)
	{
		int randIdx1 = FMath::RandRange(0, 3);
		int randIdx2 = FMath::RandRange(0, 3);

		int temp = dirSeq[randIdx1];
		dirSeq[randIdx1] = dirSeq[randIdx2];
		dirSeq[randIdx2] = temp;
	}

	for (int i = 0; i < 4; ++i)
	{
		int nx = x;
		int ny = y;
		if (0 == dirSeq[i])  nx += 2;
		else if (1 == dirSeq[i]) ny += 2;
		else if (2 == dirSeq[i]) nx -= 2;
		else if (3 == dirSeq[i]) ny -= 2;

		if (nx < 1 || ny < 1 || nx > MAZE_LEN - 2 || ny > MAZE_LEN - 2) continue;
		if (0 == mMaze[nx][ny])   continue;
		GenerateMaze(nx, ny, dirSeq[i]);
	}
}

void ATestMaze::SelectItemLoc()
{
	int32 ItemLocCandidateNum = mItemCoords.Num() / 2;
	for (int i = 0; i < 100; ++i)
	{
		int32 RandIdx1 = FMath::RandRange(0, ItemLocCandidateNum - 1) * 2;
		int32 RandIdx2 = FMath::RandRange(0, ItemLocCandidateNum - 1) * 2;
		int32 tempX = mItemCoords[RandIdx1];
		int32 tempY = mItemCoords[RandIdx1 + 1];
		mItemCoords[RandIdx1] = mItemCoords[RandIdx2];
		mItemCoords[RandIdx1 + 1] = mItemCoords[RandIdx2 + 1];
		mItemCoords[RandIdx2] = tempX;
		mItemCoords[RandIdx2 + 1] = tempY;
	}
	for (int i = 0; i < mItemNum; ++i)
	{
		mMaze[mItemCoords[2 * i]][mItemCoords[2 * i + 1]] = 2;
	}
}

void ATestMaze::SpawnMaze()
{
	int32 Inter = 384;
	for (int i = 0; i < MAZE_LEN; ++i)
	{
		for (int j = 0; j < MAZE_LEN; ++j)
		{
			FVector SpawnLoc = 
				GetActorLocation() + FVector(i * Inter, j * Inter, 256);
			if (MAZE_LEN - 1 == i && MAZE_LEN - 2 == j)
			{
				// Spawn Door
				mExitDoor = GetWorld()->SpawnActor<ATestDoor>(
					ATestDoor::StaticClass(),
					SpawnLoc + FVector(0, 0, 6.5f),
					FRotator::ZeroRotator);
				mExitDoor->DisableCollision();
				mExitDoor->SetActorScale3D(FVector(1.f, 1.9f, 1.75f));
				continue;
			}
			if (2 == mMaze[i][j])
			{
				//Spawn Item
				GetWorld()->SpawnActor<ATestItem>(
					ATestItem::StaticClass(),
					SpawnLoc - FVector(0, 0, 206),
					FRotator::ZeroRotator)->SetMaze(this);
				continue;
			}
			if (0 == mMaze[i][j])	continue;
			GetWorld()->SpawnActor<AActor>(
				mWall, SpawnLoc, FRotator::ZeroRotator);
		}
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