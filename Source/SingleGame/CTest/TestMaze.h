// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestDoor.h"

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "TestMaze.generated.h"

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

protected:
	void GenerateMaze();
	void SpawnItem();

public:
	void DecreaseItem();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)
	int32 mItemNum = 5;

	UPROPERTY(EditAnywhere)
	ATestDoor* mExitDoor;

	TSubclassOf<AActor> mWall;

	int32 mMazeLen = 15;
	
	TArray<int32> mMaze;
};
