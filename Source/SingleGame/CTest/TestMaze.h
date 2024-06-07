// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestDoor.h"

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "TestMaze.generated.h"

// must be odd number
#define MAZE_LEN 11

class ATestItem;

UCLASS()
class SINGLEGAME_API ATestMaze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestMaze();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateMaze(int32 x, int32 y, int32 dir); // dir => 0 : 위, 1 : 오른쪽, 2 : 아래, 3 : 왼쪽
	void SelectItemLoc();

protected:
	void SpawnMaze();

public:
	void DecreaseItem();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)
	int32 mItemNum = 8;

	UPROPERTY(EditAnywhere)
	ATestDoor* mExitDoor;

	TSubclassOf<AActor> mWall;
	
	int32 mMaze[MAZE_LEN][MAZE_LEN];	// 0: 길, 1 : 벽
	TArray<int32> mItemCoords;
};
