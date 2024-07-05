// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolPoint.h"

// Sets default values
AAIPatrolPoint::AAIPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

#if WITH_EDITORONLY_DATA
	mRoot->bVisualizeComponent = true;

	mArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	mArrowComponent->ArrowColor = FColor(150, 200, 255);
	mArrowComponent->bTreatAsASprite = true;
	mArrowComponent->SetupAttachment(mRoot);
	mArrowComponent->bIsScreenSizeScaled = true;
	mArrowComponent->SetSimulatePhysics(false);
#endif
}

// Called when the game starts or when spawned
void AAIPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

