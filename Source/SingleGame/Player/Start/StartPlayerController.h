// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStartPlayerController();

protected:
	virtual void BeginPlay();

protected:
	TSubclassOf<class UStartWidget> mWidgetClass;
	class UStartWidget* mWidget;
};
