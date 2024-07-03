// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../AIInfo.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_TraceTarget.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API UBTTask_TraceTarget : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_TraceTarget();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);


};
