// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDefaultAnimTemplate.h"
#include "AIController.h"
#include "MonsterPawn.h"
#include "MonsterDataManager.h"

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

void UMonsterDefaultAnimTemplate::SetAnimData(const FName& Key)
{
	const FMonsterAnimData* AnimData = MonsterDataManager::GetInst()->FindAnim(Key);
}
