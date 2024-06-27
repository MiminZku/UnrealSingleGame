// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerLocomotionTemplate.generated.h"

/**
 *
 */
UCLASS()
class SINGLEGAME_API UPlayerLocomotionTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	UAnimSequence* GetAnimSequence(const FString& Name);

	void SetIdleAnimation(UAnimSequence* Animation) { mIdle = Animation; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bJump = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOPitch = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJogStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJogStop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpApex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpLand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAnimSequence* mJumpRecovery;
};
