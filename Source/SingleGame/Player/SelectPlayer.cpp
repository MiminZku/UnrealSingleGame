// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"
#include "SelectPawn.h"
#include "../UI/CharacterSelect/CharacterSelectWidget.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(mRoot);
	mCamera->SetupAttachment(mRoot);

	static ConstructorHelpers::FClassFinder<UCharacterSelectWidget>
		Widget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_UI/CharacterSelect/WB_CharacterSelect.WB_CharacterSelect_C'"));
	if (Widget.Succeeded())
		mWidgetClass = Widget.Class;
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// InputMode 3가지
	// GameOnly : 기본으로 설정, 커서가 화면 가운데에 락 걸리고 UI 클릭 불가능
	// UIOnly : 커서 락이 풀리며 UI들을 클릭할 수 있게 해줌
	// GameAndUI : 둘다 해줌
	FInputModeGameAndUI Mode;
	GetController<APlayerController>()->SetInputMode(Mode);
	GetController<APlayerController>()->SetShowMouseCursor(true);

	if (IsValid(mWidgetClass))
	{
		mWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(),
			mWidgetClass);
		
		if (IsValid(mWidget))
			mWidget->AddToViewport(/* 그리는 순서 */);
	}
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	bool Collision = GetController<APlayerController>()->
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	if (Collision)
	{
		ASelectPawn* SelectPawn = Cast<ASelectPawn>(HitResult.GetActor());
		if (IsValid(SelectPawn))	mOnMouseActor = SelectPawn;
	}
	else
	{

	}
}

// Called to bind functionality to input
void ASelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

