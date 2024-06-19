// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleGamePlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Input/DefaultInputData.h"
#include "PlayerAnimInstance.h"

// Sets default values
ASingleGamePlayer::ASingleGamePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void ASingleGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// 클래스 디폴트 오브젝트(CDO)를 얻어온다.
		const UDefaultInputData* InputData = GetDefault<UDefaultInputData>();

		Subsystem->AddMappingContext(InputData->mDefaultContext, 0 /* 우선순위 */);
	}
}

// Called every frame
void ASingleGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASingleGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		// 클래스 디폴트 오브젝트(CDO)를 얻어온다.
		const UDefaultInputData* InputData = GetDefault<UDefaultInputData>();

		EnhancedInputComponent->BindAction(InputData->mMove,
			ETriggerEvent::Triggered,
			this, &ASingleGamePlayer::MoveAction);

		EnhancedInputComponent->BindAction(InputData->mRotate,
			ETriggerEvent::Triggered,
			this, &ASingleGamePlayer::RotateAction);

		EnhancedInputComponent->BindAction(InputData->mJump,
			ETriggerEvent::Triggered,
			this, &ASingleGamePlayer::JumpAction);

		EnhancedInputComponent->BindAction(InputData->mAttack,
			ETriggerEvent::Triggered,
			this, &ASingleGamePlayer::AttackAction);
	}
}

void ASingleGamePlayer::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();

	FVector dir = GetActorForwardVector() * Axis.X;
	dir += GetActorRightVector() * Axis.Y;

	AddMovementInput(dir, 1.f);

	mAnimInstance->SetMoveDir(dir);
}

void ASingleGamePlayer::RotateAction(const FInputActionValue& Value)
{
	FVector2D Axis2D = Value.Get<FVector2D>();

	AddControllerYawInput(Axis2D.X);
	AddControllerPitchInput(-Axis2D.Y);
}

void ASingleGamePlayer::JumpAction(const FInputActionValue& Value)
{
	if (GEngine)
	{
		// viewport에 원하는 문자열 출력
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("Jump"));
	}
}

void ASingleGamePlayer::AttackAction(const FInputActionValue& Value)
{
	if (GEngine)
	{
		// viewport에 원하는 문자열 출력
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("Attack"));
	}
}