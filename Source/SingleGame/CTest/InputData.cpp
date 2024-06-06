// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	{
		// �𸮾� ������ �ҷ��� �� ��� (�ּ� ��Ŭ�� -> ���۷��� ����)
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_TestIMC.IMC_TestIMC'"));

		// ���������� �ε������� �Ǵ�
		if (Asset.Succeeded())
		{
			// �������� ��� �ҷ��� �ּ��� ��������� ����
			mDefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestMove.IA_TestMove'"));

		if (Asset.Succeeded())
		{
			mMove = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestFire.IA_TestFire'"));

		if (Asset.Succeeded())
		{
			mFire = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestRotation.IA_TestRotation'"));

		if (Asset.Succeeded())
		{
			mRotate = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestShield.IA_TestShield'"));

		if (Asset.Succeeded())
		{
			mSheild = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Test/TestInput/IA_TestFireRolling.IA_TestFireRolling'"));

		if (Asset.Succeeded())
		{
			mFireRolling = Asset.Object;
		}
	}
}
