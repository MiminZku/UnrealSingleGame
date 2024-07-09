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
	Death,
	Hit,
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

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_HitEnd();

	void SetAnimData(const FName& Key);
	void PlayMontage(const FString& Name);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterDefaultAnim mMonsterAnim = EMonsterDefaultAnim::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimSequence*> mSequenceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UBlendSpace*> mBlendSpaceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimMontage*> mMontageMap;
};
