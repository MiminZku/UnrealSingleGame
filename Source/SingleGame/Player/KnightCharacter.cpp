// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"
#include "PlayerAnimInstance.h"

AKnightCharacter::AKnightCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -94.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>
	//	AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/_Player/Knight/ABP_Knight.ABP_Knight_C'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/_Player/Knight/ABP_Kwang_TemplateLink.ABP_Kwang_TemplateLink_C'"));
	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	mSwordCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollisionBox"));
	// 매쉬 소켓에 붙임
	mSwordCollisionBox->SetupAttachment(GetMesh(), TEXT("weapon_r_collision"));
	mSwordCollisionBox->SetBoxExtent(FVector(3.f, 65.f, 15.f));
	mSwordCollisionBox->SetCollisionProfileName(TEXT("PlayerAttack"));
	mSwordCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));
	if (HitAsset.Succeeded())
	{
		mNormalAttackHitParticle = HitAsset.Object;
	}
}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	mAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	mSwordCollisionBox->OnComponentBeginOverlap.AddDynamic(this,
		&AKnightCharacter::SwordBeginOverlap);
	mSwordCollisionBox->OnComponentEndOverlap.AddDynamic(this,
		&AKnightCharacter::SwordEndOverlap);
}

void AKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKnightCharacter::NormalAttack()
{
	mAnimInstance->PlayAttackMontage(mCombo);
}

void AKnightCharacter::AttackEnable()
{
	mSwordCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
	FVector End = Start + GetActorForwardVector() * 200.f;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	TArray<FHitResult> hitResultArr;
	bool Collision = GetWorld()->SweepMultiByChannel(hitResultArr, Start, End,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel17,
		FCollisionShape::MakeSphere(50.f), params);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f,
		100.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 1.f);
#endif

	if (Collision)
	{
		for (FHitResult& hitResult : hitResultArr)
		{
			FDamageEvent DmgEvent;
			hitResult.GetActor()->TakeDamage(10.f, DmgEvent, GetController(), this);
		}
	}
}

void AKnightCharacter::AttackDisable()
{
	mSwordCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKnightCharacter::SwordBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//FDamageEvent DmgEvent;
	//OtherActor->TakeDamage(10.f, DmgEvent, GetController(), this);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("begin overlap"));
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mNormalAttackHitParticle,
		OtherActor->GetActorLocation());
}

void AKnightCharacter::SwordEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("end overlap"));
	}
}