// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultInputData.h"

UDefaultInputData::UDefaultInputData()
{
	{
		// 언리얼 에셋을 불러올 때 사용 (애셋 우클릭 -> 레퍼런스 복사)
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_Input/IMC_Main.IMC_Main'"));

		// 정상적으로 로딩헀는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 애셋을 멤버변수에 지정
			mDefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/_Input/IA_Move.IA_Move'"));

		if (Asset.Succeeded())
		{
			mMove = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/_Input/IA_Rotate.IA_Rotate'"));

		if (Asset.Succeeded())
		{
			mRotate = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/_Input/IA_Jump.IA_Jump'"));

		if (Asset.Succeeded())
		{
			mJump = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/_Input/IA_Attack.IA_Attack'"));

		if (Asset.Succeeded())
		{
			mAttack = Asset.Object;
		}
	}
}
