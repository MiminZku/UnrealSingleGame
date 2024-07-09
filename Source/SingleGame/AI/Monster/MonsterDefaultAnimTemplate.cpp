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

void UMonsterDefaultAnimTemplate::AnimNotify_DeathEnd()
{
	TryGetPawnOwner()->Destroy();
}

void UMonsterDefaultAnimTemplate::AnimNotify_HitEnd()
{
	//AAIPawn* Pawn = Cast<AAIPawn>(TryGetPawnOwner());
	//if (IsValid(Pawn))
	//{
	//	Pawn->SetState(EAIState::Idle);
	//}
}

void UMonsterDefaultAnimTemplate::SetAnimData(const FName& Key)
{
	const FMonsterAnimData* AnimData = MonsterDataManager::GetInst()->FindAnim(Key);

	if (AnimData)
	{
		mSequenceMap = AnimData->mSequenceMap;
		mBlendSpaceMap = AnimData->mBlendSpaceMap;
		mMontageMap = AnimData->mMontageMap;
	}
}

void UMonsterDefaultAnimTemplate::PlayMontage(const FString& Name)
{
	UAnimMontage** Montage = mMontageMap.Find(Name);
	if (Montage)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		//	TEXT("Play Montage"));
		Montage_SetPosition(*Montage, 0.f);
		Montage_Play(*Montage);
	}
}
