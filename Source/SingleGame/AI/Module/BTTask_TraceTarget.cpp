// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TraceTarget.h"
#include "../AIPawn.h"
#include "../Monster/MonsterPawn.h"
#include "AIController.h"

UBTTask_TraceTarget::UBTTask_TraceTarget()
{
	NodeName = TEXT("BTT_TraceTarget");
	AcceptableRadius = 50.f;
	BlackboardKey.SelectedKeyName = MonsterDefaultKey::mTarget;
}

EBTNodeResult::Type UBTTask_TraceTarget::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();
	if (IsValid(AIPawn))
	{
		AIPawn->SetState(EAIState::Trace);
		AMonsterPawn* MonsterPawn = Cast<AMonsterPawn>(AIPawn);
		if (IsValid(MonsterPawn))
		{
			AcceptableRadius = MonsterPawn->GetAttackDistance();
		}
	}

	return Result;
}

EBTNodeResult::Type UBTTask_TraceTarget::AbortTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);


	return Result;
}

void UBTTask_TraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_TraceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
