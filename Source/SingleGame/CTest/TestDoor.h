// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "TestDoor.generated.h"

enum class EDoorState
{
	Closed,
	Opening,
	Opened,
	Closing,
	End
};

UCLASS()
class SINGLEGAME_API ATestDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()	
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

public:
	void OpenDoor();
	void CloseDoor();

protected:
	// 6면체 충돌체
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBoxCollision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;

	float mRotateSpeed = 100.f;
	EDoorState mState = EDoorState::Closed;
	// true : forward 방향으로 열림, false : 반대방향으로 열림
	bool bDir = true;	
};
