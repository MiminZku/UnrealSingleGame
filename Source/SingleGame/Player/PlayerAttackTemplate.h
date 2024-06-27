// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAttackTemplate.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API UPlayerAttackTemplate : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAcceleration = false;
};
