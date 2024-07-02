// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API AMonsterController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetTeamId(uint8 ID) { mTeamID = ID; }
	virtual FGenericTeamId GetGenericTeamId() const;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

private:
	UFUNCTION()
	void OnTargetDetect(AActor* Target, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetForget(AActor* Target);



protected:
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* mAIPerception;

	UAISenseConfig_Sight* mSightConfig;

	//UAISenseConfig_Damage* mDamageConfig;

	UBehaviorTree* mBehaviorTree;
	UBlackboardData* mBlackBoard;

	uint8 mTeamID = 255;
};
