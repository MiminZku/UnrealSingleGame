// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "SingleGamePlayer.h"
#include "KnightCharacter.h"

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

	// �¿�
	ActionValue.Y;	// 1 �̸� 90, -1 �̸� -90

	// ����
	ActionValue.X; //1 �̸� 0.5 ���ϰ�, -1 �̸� 1.5 ���ϱ�


	mMoveDir = ActionValue.Y * 90 * (1 - ActionValue.X * 0.5f);
}

void UPlayerAnimInstance::PlayAttackMontage(int& Combo)
{
	if (!IsValid(mAttackMontage)) return;

	// ��Ÿ�ְ� �̹� ��� ������ ���� ���� ���
	//if (!mAttackState)
	//{
	//	if (!Montage_IsPlaying(mAttackMontage))
	//	{
	//		Montage_Play(mAttackMontage, 1.f/*��� �ӵ�*/);
	//		Montage_JumpToSection(mAttackSectionName[mCurrentAttackSection]);
	//	}
	//}
	//else
	//	mAttackCombo = true;
	//mAttackState = true;

	if (Montage_IsPlaying(mAttackMontage) || Montage_IsPlaying(mAttackRecoveryMontage))
	{
		++Combo;
		Combo %= mAttackSectionName.Num();
	}
	Montage_Play(mAttackMontage, 1.f/*��� �ӵ�*/);
	Montage_JumpToSection(mAttackSectionName[Combo]);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			1.f, FColor::Blue, FString::Printf(TEXT("%d"), Combo));
	}
}

void UPlayerAnimInstance::PlayAttackRecoveryMontage(int32 Combo)
{
	Montage_Play(mAttackRecoveryMontage, 1.f);
	Montage_JumpToSection(mAttackSectionName[Combo]);
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	// Combo Ÿ�ֿ̹� ����Ű �����ٸ�
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
	AKnightCharacter* Knight = Cast<AKnightCharacter>(TryGetPawnOwner());
	if (Montage == mAttackMontage && !bInterrupted)
	{
		if (IsValid(Knight))
		{
			if (Knight->GetCombo() != mAttackSectionName.Num() - 1)
			{
				PlayAttackRecoveryMontage(Knight->GetCombo());
			}
			Knight->SetCombo(0);
		}
	}
	else if (Montage == mAttackRecoveryMontage && !bInterrupted)
	{
		if (IsValid(Knight))
		{
			Knight->SetCombo(0);
		}
	}
	//if (Montage == mAttackMontage && !bInterrupted)
	//{		
	//	mAttackCombo = false;
	//	mAttackState = false;
	//	mCurrentAttackSection = 0;
	//
	//	if (mCurrentAttackSection != mAttackSectionName.Num() - 1)
	//	{
	//		PlayAttackRecoveryMontage();
	//	}
	//}
	//else if (Montage == mAttackRecoveryMontage)
	//{
	//	mAttackCombo = false;
	//	mAttackState = false;
	//	mCurrentAttackSection = 0;
	//}
}
