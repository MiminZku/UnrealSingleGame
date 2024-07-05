// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIInfo.h"
#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPoint.generated.h"

UCLASS()
class SINGLEGAME_API AAIPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
#if WITH_EDITORONLY_DATA
	UArrowComponent* mArrowComponent;
#endif

	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;
};
