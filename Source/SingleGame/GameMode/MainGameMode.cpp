// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../Player/KnightCharacter.h"
#include "../AI/Monster/MonsterDataManager.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = AKnightCharacter::StaticClass();

	MonsterDataManager::GetInst()->Init();
}

AMainGameMode::~AMainGameMode()
{
	MonsterDataManager::DestroyInst();
}
