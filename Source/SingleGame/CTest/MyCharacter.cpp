// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputData.h"
#include "TestShield.h"
#include "TestBullet.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mShieldRotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldRotationPivot"));
	mRotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));

	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);
	mShieldRotationPivot->SetupAttachment(RootComponent);
	mRotatingMovement->SetUpdatedComponent(mShieldRotationPivot);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -94.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	mSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	mSpringArm->TargetArmLength = 600.f;
	mSpringArm->bUsePawnControlRotation = true;

	//bUseControllerRotationYaw = true;

	//mTestBullet = LoadObject<UBlueprint>(nullptr,
	//	TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestBullet.BP_TestBullet'"));

	//m_TestShield = LoadObject<UBlueprint>(nullptr,
	//	TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestShield.BP_TestShield'"));

	// class finder ��� �� ���۷��� ���� �ݵ�� _C �ٿ��־�� ��
	static ConstructorHelpers::FClassFinder<AActor>
		TestBullet(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestBullet.BP_TestBullet_C'"));
	if (TestBullet.Succeeded())
	{
		mTestBullet = TestBullet.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor>
		TestShield(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestShield.BP_TestShield_C'"));
	if (TestShield.Succeeded())
	{
		mTestShield = TestShield.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor>
		TestRollingBullet(TEXT("/Script/Engine.Blueprint'/Game/Test/TestBlueprint/BP_TestRollingBullet.BP_TestRollingBullet_C'"));
	if (TestRollingBullet.Succeeded())
	{
		mTestRollingBullet = TestRollingBullet.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Test/TestAnimation/ABP_MyCharacter.ABP_MyCharacter_C'"));
	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimClass.Class);
	}

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	
	//GetCharacterMovement()->MaxWalkSpeed = 1200.f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���� ĳ���Ϳ� ���ǵǾ� �ִ� ��Ʈ�ѷ��� Player Controller�� �´��� Ȯ���ϰ�
	// �´ٸ� EnhancedInputSUbsystem�� ������ �Ѵ�.
	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// Ŭ���� ����Ʈ ������Ʈ(CDO)�� ���´�.
		const UTestInputData* InputData = GetDefault<UTestInputData>();

		Subsystem->AddMappingContext(InputData->mDefaultContext, 0 /* �켱���� */);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (false == bCanSpawnShield)
	{
		//mShieldRotationPivot->AddLocalRotation(FRotator(0, 120 * DeltaTime, 0));
		mShieldTime += DeltaTime;
	}

	if (mShieldTime >= mShieldCoolTime)
	{
		mShieldTime = 0;
		bCanSpawnShield = true;
	}

	if (GEngine)
	{
	// viewport�� ���ϴ� ���ڿ� ���
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue,
		FString::Printf(TEXT("Velocity : %.1f"), GetVelocity().Size()));
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		// Ŭ���� ����Ʈ ������Ʈ(CDO)�� ���´�.
		const UTestInputData* InputData = GetDefault<UTestInputData>();

		EnhancedInputComponent->BindAction(InputData->mMove,
			ETriggerEvent::Triggered,
			this, &AMyCharacter::MoveAction);

		EnhancedInputComponent->BindAction(InputData->mRotate,
			ETriggerEvent::Triggered,
			this, &AMyCharacter::RotateAction);

		EnhancedInputComponent->BindAction(InputData->mFire,
			ETriggerEvent::Started,
			this, &AMyCharacter::FireAction);

		EnhancedInputComponent->BindAction(InputData->mFireRolling,
			ETriggerEvent::Started,
			this, &AMyCharacter::FireRollingAction);

		EnhancedInputComponent->BindAction(InputData->mSheild,
			ETriggerEvent::Started,
			this, &AMyCharacter::ShieldAction);
	}
}

void AMyCharacter::SpawnShield()
{
	if (false == bCanSpawnShield)	return;
	bCanSpawnShield = false;

	mShieldSpawnDegree = 0.f;
	//mShieldRotationPivot->SetRelativeRotation(FRotator::ZeroRotator);

	for (int32 i = 0; i < mShieldNum; ++i)
	{
		FVector loc = mShieldRotationPivot->GetComponentLocation();
		loc += mShieldRotationPivot->GetForwardVector() *
			mDistanceToShield * FMath::Cos(mShieldSpawnDegree * 3.141592f / 180.f);
		loc += mShieldRotationPivot->GetRightVector() *
			mDistanceToShield * FMath::Sin(mShieldSpawnDegree * 3.141592f / 180.f);

		FRotator rot =
			FRotator(0, mShieldSpawnDegree, 0) + mShieldRotationPivot->GetComponentRotation();

		AActor* ShieldInstance =
			//GetWorld()->SpawnActor<AActor>(
			//	//mTestShield->GeneratedClass,
			//	mTestShield,
			//	loc, rot);

			// Class�̸�::StaticClass() => UClass ������ �����´�.
			GetWorld()->SpawnActor<ATestShield>(
				ATestShield::StaticClass(), loc, rot);


		ShieldInstance->AttachToComponent(mShieldRotationPivot,
			//FAttachmentTransformRules(
			//	EAttachmentRule::KeepWorld,
			//	EAttachmentRule::KeepRelative,
			//	EAttachmentRule::KeepRelative,
			//	true)
			FAttachmentTransformRules::KeepWorldTransform
		);

		mShieldSpawnDegree += 360.f / mShieldNum;
	}
	if (mShieldNum < mMaxShieldNum)	++mShieldNum;
}


void AMyCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();

	//if (GEngine)
	//{
	//	// viewport�� ���ϴ� ���ڿ� ���
	//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue,
	//		FString::Printf(TEXT("X : %.1f Y : %1.f"), Axis.X, Axis.Y));
	//}

	FVector dir = GetActorForwardVector() * Axis.X;
	dir += GetActorRightVector() * Axis.Y;
	dir += GetActorUpVector() * Axis.Z;

	AddMovementInput(dir, 1.f);
}

void AMyCharacter::RotateAction(const FInputActionValue& Value)
{
	FVector2D Axis2D = Value.Get<FVector2D>();

	AddControllerYawInput(Axis2D.X);
	AddControllerPitchInput(-Axis2D.Y);
}

void AMyCharacter::FireAction(const FInputActionValue& Value)
{
	FVector loc = GetActorLocation() + GetActorForwardVector() * 100;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::Undefined;

	// GetWorld()�� �����ڿ��� ��� X
	//GetWorld()->SpawnActor<AActor>(
	//	//mTestBullet->GeneratedClass,
	//	mTestBullet,
	//	loc, GetActorRotation(), param);

	GetWorld()->SpawnActor<ATestBullet>(
		ATestBullet::StaticClass(),
		loc, GetActorRotation(), param)->SetOwnerController(GetController());

	GetWorld()->SpawnActor<ATestBullet>(
		ATestBullet::StaticClass(),
		loc + GetActorRightVector() * -75,
		GetActorRotation() + FRotator(0, -15.f, 0),
		param)->SetOwnerController(GetController());

	GetWorld()->SpawnActor<ATestBullet>(
		ATestBullet::StaticClass(),
		loc + GetActorRightVector() * 75,
		GetActorRotation() + FRotator(0, 15.f, 0),
		param)->SetOwnerController(GetController());
}

void AMyCharacter::FireRollingAction(const FInputActionValue& Value)
{
	FVector loc = GetActorLocation() + GetActorForwardVector() * 100;

	GetWorld()->SpawnActor<AActor>(
		mTestRollingBullet,
		loc, GetActorRotation());
}

void AMyCharacter::ShieldAction(const FInputActionValue& Value)
{
	SpawnShield();
}
