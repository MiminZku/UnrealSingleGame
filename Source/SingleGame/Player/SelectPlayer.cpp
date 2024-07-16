// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"
#include "SelectPawn.h"
#include "../Input/DefaultInputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

	//if (IsValid(mWidgetClass))
	//{
	//	mWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(),
	//		mWidgetClass);
	//	
	//	if (IsValid(mWidget))
	//		mWidget->AddToViewport(/* 그리는 순서 */);
	//}

	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// 클래스 디폴트 오브젝트(CDO)를 얻어온다.
		const USelectInputData* InputData = GetDefault<USelectInputData>();

		Subsystem->AddMappingContext(InputData->mSelectContext, 0 /* 우선순위 */);
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
		if (IsValid(SelectPawn))
		{
			mOnMouseActor = SelectPawn;
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Black,
				mOnMouseActor->GetName());
			mOnMouseActor->OnMouse(true);
		}
		else
		{
			mOnMouseActor = nullptr;
		}
	}
	else
	{
		if (mOnMouseActor)
		{
			mOnMouseActor->OnMouse(false);
		}
		mOnMouseActor = nullptr;
	}
}

// Called to bind functionality to input
void ASelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		// 클래스 디폴트 오브젝트(CDO)를 얻어온다.
		const USelectInputData* InputData = GetDefault<USelectInputData>();

		EnhancedInputComponent->BindAction(InputData->mSelect,
			ETriggerEvent::Started,
			this, &ASelectPlayer::ClickAction);
	}
}

void ASelectPlayer::ClickAction(const FInputActionValue& Value)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, 
	//	Value.ToString());

	if (!mOnMouseActor)	return;

	FString Option = FString::Printf(TEXT("Job = %d"), (int32)mOnMouseActor->GetJob());

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true, Option);
}