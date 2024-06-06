// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../GameInfo.h"
#include "InputActionValue.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class SINGLEGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

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
	void FireAction(const FInputActionValue& Value);
	void FireRollingAction(const FInputActionValue& Value);
	void ShieldAction(const FInputActionValue& Value);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* mShieldRotationPivot;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* mRotatingMovement;

	//UBlueprint* mTestBullet;
	//UBlueprint* mTestShield;

	// TSubclassOf : UClass 정보를 저장하는 템플릿 객체
	TSubclassOf<AActor> mTestBullet;
	TSubclassOf<AActor> mTestRollingBullet;
	TSubclassOf<AActor> mTestShield;

	bool bCanSpawnShield = true;
	int mShieldNum = 1;
	float mDistanceToShield = 200.f;
	float mShieldTime = 0.f;
	float mShieldCoolTime = 4.f;
	float mShieldSpawnDegree = 0.f;
};
