// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalBase.h"

// Sets default values
ADecalBase::ADecalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	SetRootComponent(mRoot);

	mDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	mDecal->DecalSize = FVector(128, 256, 256);
	mDecal->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void ADecalBase::BeginPlay()
{
	Super::BeginPlay();

	mDynamicMaterial = mDecal->CreateDynamicMaterialInstance();
	if (mDynamicMaterial)
		 mDynamicMaterial->GetScalarParameterValue(
			FHashedMaterialParameterInfo(TEXT("Opacity")), mOpacity);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
	//	FString::Printf(TEXT("Opacity : %f"), mOpacity));
}

// Called every frame
void ADecalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(mOpacity > 0)	mOpacity -= DeltaTime / 5.f;	// 5ÃÊ ÈÄ¿¡ 0 µÊ

	if (mDynamicMaterial)
		mDynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), mOpacity);
}

void ADecalBase::SetOriginMaterial(UMaterialInterface* Material)
{
	mDecal->SetDecalMaterial(Material);
	mDynamicMaterial = mDecal->CreateDynamicMaterialInstance();
}

