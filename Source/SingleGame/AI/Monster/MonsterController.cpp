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


	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BehaviorTree(TEXT("/Script/AIModule.BehaviorTree'/Game/_AI/Monsters/BT_MonsterDefault.BT_MonsterDefault'"));
	if (BehaviorTree.Succeeded())
	{
		mBehaviorTree = BehaviorTree.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BlackBoard(TEXT("/Script/AIModule.BlackboardData'/Game/_AI/Monsters/BB_MonsterDefault.BB_MonsterDefault'"));
	if (BlackBoard.Succeeded())
	{
		mBlackBoard = BlackBoard.Object;
	}

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

	if (IsValid(mBehaviorTree) && IsValid(mBlackBoard))	// GameInfo에서 include 해줘야 함
	{
		UBlackboardComponent* BlackboardRef = nullptr;
		if (UseBlackboard(mBlackBoard, BlackboardRef))
		{
			RunBehaviorTree(mBehaviorTree);
		}
	}
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
		//AController* Controller = Cast<AController>(Target);
		//if (IsValid(Controller))
		//{
		//	Target = Controller->GetPawn<AActor>();
		//}
		

		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
			TEXT("Detected Target"));

		if (Target->ActorHasTag(TEXT("Player")) &&
			Target != Blackboard->GetValueAsObject(TEXT("Target")))
		{
			Blackboard->SetValueAsObject(TEXT("Target"), Target);
		}
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			TEXT("Lost Target"));

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}


}

void AMonsterController::OnTargetForget(AActor* Target)
{
}
