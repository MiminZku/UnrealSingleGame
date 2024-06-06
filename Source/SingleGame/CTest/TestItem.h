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
	// ��������Ʈ ��� �Լ��� �ݵ�� UFUNCTION ��ũ�� �ٿ���� ��
	UFUNCTION()	// �������Ʈ���� ȣ�� ������ �ɼ� ���� ����
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
	// 6��ü �浹ü
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mBody;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
};
