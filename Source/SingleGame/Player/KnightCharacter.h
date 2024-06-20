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
};
