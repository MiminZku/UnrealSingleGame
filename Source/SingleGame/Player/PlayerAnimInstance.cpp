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

		mIdleAOPitch = Player->GetBaseAimRotation().Pitch;
		mIdleAOYaw = Player->GetBaseAimRotation().Yaw;		
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

	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);
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

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage)) return;

	// 몽타주가 이미 재생 중이지 않을 때만 재생
	if (!mAttackState)
	{
		if (!Montage_IsPlaying(mAttackMontage))
		{
			Montage_Play(mAttackMontage, 1.f/*재생 속도*/);
			Montage_JumpToSection(mAttackSectionName[mCurrentAttackSection]);
		}
	}

	else
		mAttackCombo = true;

	mAttackState = true;
}

void UPlayerAnimInstance::PlayAttackRecoveryMontage()
{
	Montage_Play(mAttackRecoveryMontage);
	Montage_JumpToSection(mAttackSectionName[mCurrentAttackSection]);
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	// Combo 타이밍에 공격키 눌렀다면
	if (mAttackCombo)
	{
		++mCurrentAttackSection;
		mCurrentAttackSection %= mAttackSectionName.Num();

		Montage_Play(mAttackMontage);
		Montage_JumpToSection(mAttackSectionName[mCurrentAttackSection]);

		mAttackCombo = false;
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	ASingleGamePlayer* Player = Cast<ASingleGamePlayer>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->AttackEnable();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackDisable()
{
	ASingleGamePlayer* Player = Cast<ASingleGamePlayer>(TryGetPawnOwner());

	if (IsValid(Player))
	{
		Player->AttackDisable();
	}
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == mAttackMontage && !bInterrupted)
	{
		mAttackCombo = false;
		mAttackState = false;
		mCurrentAttackSection = 0;

		if (mCurrentAttackSection != mAttackSectionName.Num() - 1)
		{
			PlayAttackRecoveryMontage();
		}
		else
		{
		}
	}
	else if (Montage == mAttackRecoveryMontage)
	{
		mAttackCombo = false;
		mAttackState = false;
		mCurrentAttackSection = 0;
	}
}
