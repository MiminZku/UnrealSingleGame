// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnActor.h"
#include "AIPawn.h"
#include "AIPatrolPoint.h"

// Sets default values
AAISpawnActor::AAISpawnActor()
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
void AAISpawnActor::BeginPlay()
{
	Super::BeginPlay();

	// 스폰된 위치도 패트롤 포인트로 추가
	mPatrolPointArr.Add(
		GetWorld()->SpawnActor<AAIPatrolPoint>(AAIPatrolPoint::StaticClass(),
			GetActorLocation(), GetActorRotation()));
}

// Called every frame
void AAISpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime;

	if (bFirstSpawn)
	{
		bFirstSpawn = false;
		if (mTime >= mFirstSpawnTime)
		{
			mTime = 0.f;
			Spawn();
		}
	}
	else
	{
		if (mTime >= mSpawnTimeInterval && !IsValid(mSpawnActor))
		{
			mTime = 0.f;
			Spawn();
		}
	}
}

void AAISpawnActor::Spawn()
{
	if (!IsValid(mSpawnClass))	return;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector SpawnLoc = GetActorLocation();

	AAIPawn* DefaultPawn = mSpawnClass->GetDefaultObject<AAIPawn>();

	if (IsValid(DefaultPawn))
	{
		SpawnLoc.Z += DefaultPawn->GetCapsule()->GetScaledCapsuleHalfHeight();
	}

	mSpawnActor = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
		SpawnLoc, GetActorRotation(), params);

	if (IsValid(mSpawnActor))
	{
		mSpawnActor->AddDeathDelegate<ThisClass>(this, &AAISpawnActor::AIDeathDelegate);
		mSpawnActor->SetPatrolPoints(mPatrolPointArr);
		mSpawnActor->RegisterPatrolPoint();
	}
}

void AAISpawnActor::AIDeathDelegate()
{

}

