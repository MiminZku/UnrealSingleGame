// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "SelectPlayer.generated.h"

UCLASS()
class SINGLEGAME_API ASelectPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void ClickAction(const FInputActionValue& Value);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	class ASelectPawn* mOnMouseActor;

	TSubclassOf<class UCharacterSelectWidget> mWidgetClass;

	class UCharacterSelectWidget* mWidget;
};
