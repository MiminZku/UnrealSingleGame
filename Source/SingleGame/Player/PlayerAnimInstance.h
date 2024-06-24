// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SINGLEGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

	void SetMoveDir(const FVector& ActionValue);
	
	void SetHeadRotation(const float& Pitch, const float& Yaw)
	{
		mIdleAOPitch = Pitch;
		mIdleAOYaw = Yaw;
	}

	void PlayAttackMontage(int32& Combo);
	void PlayAttackRecoveryMontage(int32 Combo);

	UFUNCTION()	// 노티파이 함수들은 무조건 UFUNCTION, void
	void AnimNotify_AttackCombo();	// 이름 정해진 대로 ( AnimNotify_Notify이름() )

	UFUNCTION()	
	void AnimNotify_AttackEnable();

	UFUNCTION()	
	void AnimNotify_AttackDisable();

	// bInterrupted : 끝나기 전에 다른 몽타주 재생되면 true
	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveDir = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAir = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOPitch = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mIdleAOYaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackRecoveryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> mAttackSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttackSection = 0;

	bool mAttackCombo = false;
	bool mAttackState = false;
};