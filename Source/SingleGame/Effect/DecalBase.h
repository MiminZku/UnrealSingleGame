// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalBase.generated.h"

UCLASS()
class SINGLEGAME_API ADecalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetOriginMaterial(UMaterialInterface* Material);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* mDecal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mOriginMaterial;

	UMaterialInstanceDynamic* mDynamicMaterial;

	float		mOpacity = 1.f;
	float		mGlow = 0.f;
};
