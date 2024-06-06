// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "TestItem.generated.h"

UCLASS()
class SINGLEGAME_API ATestItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// 델리게이트 등록 함수는 반드시 UFUNCTION 매크로 붙여줘야 함
	UFUNCTION()	// 블루프린트에서 호출 가능한 옵션 설정 가능
	void CollisionBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	// 6면체 충돌체
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
};
