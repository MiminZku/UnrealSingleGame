#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "DataStructure/LinkedList.h"
#include "Animation/AimOffsetBlendSpace.h"

#include "GenericTeamAgentInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(Sac6, Warning, All)

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion,
	Soldier,
	
};