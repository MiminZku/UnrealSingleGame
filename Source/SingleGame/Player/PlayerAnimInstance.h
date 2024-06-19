// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

	void SetMoveDir(const FVector& ActionValue);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveDir = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAir = false;
};
