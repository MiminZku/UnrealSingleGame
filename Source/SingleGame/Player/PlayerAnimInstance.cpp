// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "SingleGamePlayer.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASingleGamePlayer* Player = Cast<ASingleGamePlayer>(TryGetPawnOwner());
	if (IsValid(Player))
	{
		//mMoveSpeed = Player->GetVelocity().Length();

		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			mMoveSpeed = Player->GetMovementComponent()->Velocity.Length();

			bAcceleration = Movement->GetCurrentAcceleration().Length() > 0.f;

			bIsAir = Movement->IsFalling();
		}
	}


}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::SetMoveDir(const FVector& ActionValue)
{
	mMoveDir = 0.f;

	// 좌우
	ActionValue.Y;	// 1 이면 90, -1 이면 -90

	// 전후
	ActionValue.X; //1 이면 0.5 곱하고, -1 이면 1.5 곱하기


	mMoveDir = ActionValue.Y * 90 * (1 - ActionValue.X * 0.5f);
}
