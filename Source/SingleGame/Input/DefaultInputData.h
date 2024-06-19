// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "UObject/NoExportTypes.h"
#include "DefaultInputData.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API UDefaultInputData : public UObject
{
	GENERATED_BODY()

public:
	UDefaultInputData();

public:
	UInputMappingContext* mDefaultContext = nullptr;

	UInputAction* mMove = nullptr;
	UInputAction* mRotate = nullptr;
	UInputAction* mJump = nullptr;
	UInputAction* mAttack = nullptr;
};
