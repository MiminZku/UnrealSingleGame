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

	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	mSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	mSpringArm->TargetArmLength = 600.f;
	mSpringArm->bUsePawnControlRotation = true;
	
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	Tags.Add(FName("Player"));
}

// Called when the game starts or when spawned
void ASingleGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	mCameraRotator = mSpringArm->GetRelativeRotation();

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
	FVector front = FRotator(0, GetBaseAimRotation().Yaw, 0).Vector(); front.Z = 0;
	FVector right = FRotator(0, GetBaseAimRotation().Yaw + 90, 0).Vector();; right.Z = 0;
	FVector dir = front * Axis.X + right * Axis.Y;

	AddMovementInput(dir, 1.f);

	mAnimInstance->SetMoveDir(dir);
}

void ASingleGamePlayer::RotateAction(const FInputActionValue& Value)
{
	FVector2D Axis2D = Value.Get<FVector2D>();

	float PitchDelta = -Axis2D.Y * mCameraRotateSpeed * GetWorld()->GetDeltaSeconds();
	float YawDelta = Axis2D.X * mCameraRotateSpeed * GetWorld()->GetDeltaSeconds();

	AddControllerPitchInput(PitchDelta);
	AddControllerYawInput(YawDelta);
	
	//mCameraRotator.Pitch += PitchDelta;
	//mCameraRotator.Yaw += YawDelta;

	//if (mCameraRotator.Pitch > 90)	mCameraRotator.Pitch = 90.f;
	//else if (mCameraRotator.Pitch < -90) mCameraRotator.Pitch = -90.f;

	//if (mCameraRotator.Yaw > 180)	mCameraRotator.Yaw += 360.f;
	//else if (mCameraRotator.Yaw < -180) mCameraRotator.Yaw -= 360.f;
	//
	//mAnimInstance->SetHeadRotation(mCameraRotator.Pitch, mCameraRotator.Yaw);
}

void ASingleGamePlayer::JumpAction(const FInputActionValue& Value)
{
	// 기본 캐릭터 클래스에서 지원
	if (CanJump())
	{
		mAnimInstance->OnJump();
		Jump();
	}
}

void ASingleGamePlayer::AttackAction(const FInputActionValue& Value)
{
	NormalAttack();
}

void ASingleGamePlayer::NormalAttack()
{
}

void ASingleGamePlayer::AttackEnable()
{
}

void ASingleGamePlayer::AttackDisable()
{
}

FGenericTeamId ASingleGamePlayer::GetGenericTeamId() const
{
	return FGenericTeamId(mTeamID);
}

