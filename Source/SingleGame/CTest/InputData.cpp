// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UTestInputData::UTestInputData()
{
	{
		// 언리얼 에셋을 불러올 때 사용 (애셋 우클릭 -> 레퍼런스 복사)
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Test/TestInput/IMC_TestIMC.IMC_TestIMC'"));

		// 정상적으로 로딩헀는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 애셋을 멤버변수에 지정
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
