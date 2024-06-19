// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultInputData.h"

UDefaultInputData::UDefaultInputData()
{
	{
		// �𸮾� ������ �ҷ��� �� ��� (�ּ� ��Ŭ�� -> ���۷��� ����)
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_Input/IMC_Main.IMC_Main'"));

		// ���������� �ε������� �Ǵ�
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� �ּ��� ��������� ����
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
