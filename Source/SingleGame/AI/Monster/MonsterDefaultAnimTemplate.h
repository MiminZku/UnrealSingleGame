// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../AIInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterDefaultAnimTemplate.generated.h"

UENUM(BlueprintType)
enum class EMonsterDefaultAnim : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death
};

UCLASS()
class SINGLEGAME_API UMonsterDefaultAnimTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterDefaultAnimTemplate();

public:
	void ChangeAnim(EMonsterDefaultAnim Anim)
	{
		mMonsterAnim = Anim;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterDefaultAnim mMonsterAnim = EMonsterDefaultAnim::Idle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mIdle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mWalk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* mDeath;

};
