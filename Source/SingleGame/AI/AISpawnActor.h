// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnActor.generated.h"

UCLASS()
class SINGLEGAME_API AAISpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

	UFUNCTION()
	void AIDeathDelegate();

protected:
#if WITH_EDITORONLY_DATA
	UArrowComponent* mArrowComponent;
#endif

	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIPawn> mSpawnClass;

	class AAIPawn* mSpawnActor = nullptr;

	UPROPERTY(EditAnywhere)
	float mFirstSpawnTime = 0.f;

	UPROPERTY(EditAnywhere)
	float mSpawnTimeInterval = 5.f;
};
