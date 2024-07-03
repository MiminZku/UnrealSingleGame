// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDefaultAnimTemplate.h"
#include "AIController.h"
#include "MonsterPawn.h"

UMonsterDefaultAnimTemplate::UMonsterDefaultAnimTemplate()
{
}

void UMonsterDefaultAnimTemplate::AnimNotify_Attack()
{
	AMonsterPawn* Monster = Cast<AMonsterPawn>(TryGetPawnOwner());

	if (IsValid(Monster))
	{
		Monster->Attack();
	}
}

void UMonsterDefaultAnimTemplate::AnimNotify_AttackEnd()
{
	TryGetPawnOwner()->GetController<AAIController>()->GetBlackboardComponent()
		->SetValueAsBool(MonsterDefaultKey::mAttackEnd, true);
}
