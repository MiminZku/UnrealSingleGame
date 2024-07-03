// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIPawn.h"
#include "MonsterPawn.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API AMonsterPawn : public AAIPawn
{
	GENERATED_BODY()
public:
	AMonsterPawn();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void PossessedBy(AController* NewController) override;

	virtual void SetState(EAIState State);

protected:
	UPROPERTY(VisibleAnywhere)
	class UMonsterMovement* mMovement;

};
