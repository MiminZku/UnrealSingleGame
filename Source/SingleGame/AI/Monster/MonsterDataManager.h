// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIInfo.h"
#include "../../GameInfo.h"

/**
 * 
 */
class SINGLEGAME_API MonsterDataManager
{
private:
	MonsterDataManager();
	~MonsterDataManager();

public:
	static MonsterDataManager* GetInst()
	{
		if (!mInst)
			mInst = new MonsterDataManager;
		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}

	bool Init();

	const FMonsterAnimData* FindAnim(const FName& Key);
	const FMonsterInfoData* FindInfo(const FName& Key);

public:
	static MonsterDataManager* mInst;

private:
	UDataTable* mMonsterAnimTable = nullptr;
	UDataTable* mMonsterInfoTable = nullptr;
};
