#pragma once

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackBoardComponent.h"

#include "AIInfo.generated.h"

enum class EAIState : uint8
{
	Idle,
	Patrol,
	Trace,
	Attack,
	Death,
	Hit,
};

class MonsterDefaultKey
{
public:
	static FName mTarget;
	static FName mAttackEnd;
};

USTRUCT(BlueprintType)
struct FMonsterAnimData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()	// generated.h 필요
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimSequence*> mSequenceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UBlendSpace*> mBlendSpaceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimMontage*> mMontageMap;
};

USTRUCT(BlueprintType)
struct FMonsterInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()	// generated.h 필요
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString mName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mDefense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mLife;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttackDistance;
};