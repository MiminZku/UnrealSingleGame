// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "SingleGamePlayer.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API AKnightCharacter : public ASingleGamePlayer
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AKnightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void NormalAttack() override;

public:
	virtual void AttackEnable() override;
	virtual void AttackDisable() override;

protected:
	UFUNCTION()
	void SwordBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void SwordEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* mSwordCollisionBox;
};
