// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SingleGamePlayer.generated.h"

class UPlayerAnimInstance;

UCLASS()
class SINGLEGAME_API ASingleGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASingleGamePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveAction(const FInputActionValue& Value);
	void RotateAction(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	void AttackAction(const FInputActionValue& Value);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;
};
