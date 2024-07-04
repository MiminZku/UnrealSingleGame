// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDataManager.h"

MonsterDataManager* MonsterDataManager::mInst = nullptr;

MonsterDataManager::MonsterDataManager()
{
	ConstructorHelpers::FObjectFinder<UDataTable>
		MonsterAnimTable(TEXT("/Script/Engine.DataTable'/Game/_AI/Monsters/DT_MonsterAnim.DT_MonsterAnim'"));
	if (MonsterAnimTable.Succeeded())
		mMonsterAnimTable = MonsterAnimTable.Object;
}

MonsterDataManager::~MonsterDataManager()
{
}

bool MonsterDataManager::Init()
{
	return true;
}

const FMonsterAnimData* MonsterDataManager::FindAnim(const FName& Key)
{
	return mMonsterAnimTable->FindRow<FMonsterAnimData>(Key, TEXT(""));
}
