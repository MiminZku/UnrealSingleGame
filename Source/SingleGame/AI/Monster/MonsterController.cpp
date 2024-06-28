// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

AMonsterController::AMonsterController()
{
	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	
	// AI Controller 는 PerceptionComponent를 등록할 수 있게 되어 있다.
	SetPerceptionComponent(*mAIPerception);

	// 시야를 만들어준다.
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	mSightConfig->SightRadius = 2000.f;
	mSightConfig->LoseSightRadius = 2500.f;
	mSightConfig->PeripheralVisionAngleDegrees = 60.f;
	//mSightConfig->SetMaxAge(0.f);
	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// AI Perception 배열에 추가
	mAIPerception->ConfigureSense(*mSightConfig);

	// 대표 감각기관 설정
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());

}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();

	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this,
		&AMonsterController::OnTargetDetect);

	mAIPerception->OnTargetPerceptionForgotten.AddDynamic(this,
		&AMonsterController::OnTargetForget);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMonsterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterController::OnTargetDetect(AActor* Target, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
			TEXT("Detected Target"));
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			TEXT("Lost Target"));
	}


}

void AMonsterController::OnTargetForget(AActor* Target)
{
}
