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
	GENERATED_USTRUCT_BODY()	// generated.h ÇÊ¿ä
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UAnimSequence*> mSequenceMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FString, UBlendSpace*> mBlendSpaceMap;
};