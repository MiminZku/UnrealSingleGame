// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "MonsterPawn.h"
#include "MinionMeleePawn.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API AMinionMeleePawn : public AMonsterPawn
{
	GENERATED_BODY() 
	
public:
	AMinionMeleePawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetState(EAIState State);

	virtual void Attack() override;

protected:
	class UMonsterDefaultAnimTemplate* mMinionAnim;
	UParticleSystem* mAttackParticle;
};
