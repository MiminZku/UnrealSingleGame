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

	// �¿�
	ActionValue.Y;	// 1 �̸� 90, -1 �̸� -90

	// ����
	ActionValue.X; //1 �̸� 0.5 ���ϰ�, -1 �̸� 1.5 ���ϱ�


	mMoveDir = ActionValue.Y * 90 * (1 - ActionValue.X * 0.5f);
}
