// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../AIPawn.h"
#include "AIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();
	if (IsValid(AIPawn))	AIPawn->SetState(EAIState::Attack);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIPawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn<AAIPawn>();
	if (!IsValid(AIPawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetAIOwner()->
		GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		AIPawn->SetState(EAIState::Idle);

		return;
	}

	FVector AILocation = AIPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	
	AILocation.Z -= AIPawn->GetCapsule()->GetScaledCapsuleHalfHeight();
	float Radius = AIPawn->GetCapsule()->GetScaledCapsuleRadius();
	UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());
	if (IsValid(TargetCapsule))
	{
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
		Radius += TargetCapsule->GetScaledCapsuleRadius();
	}

	bool AttackEnd = OwnerComp.GetAIOwner()->GetBlackboardComponent()
		->GetValueAsBool(MonsterDefaultKey::mAttackEnd);
	if (AttackEnd)
	{
		float Distance = FVector::Distance(AILocation, TargetLocation);
		if (Distance - Radius > 300.f)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			FVector Dir = TargetLocation - AILocation;

			FRotator Rot = Dir.Rotation();

			AIPawn->SetActorRotation(FRotator(0.f, Rot.Yaw, 0.f));
		}

		OwnerComp.GetAIOwner()->GetBlackboardComponent()
			->SetValueAsBool(MonsterDefaultKey::mAttackEnd, false);
	}
}

void UBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

}
