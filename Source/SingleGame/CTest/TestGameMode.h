// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATestGameMode();

public:
	void AddScore(int32 Score)
	{
		mScore += Score;

		UE_LOG(Sac6, Warning, TEXT("Score : %d"), mScore);
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 mScore = 0;
};
