// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBullet.h"
#include "Engine/DamageEvents.h"

// Sets default values
ATestBullet::ATestBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mSphereCollision);
	mMesh->SetupAttachment(mSphereCollision);
	mMovement->SetUpdatedComponent(mSphereCollision);

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh>
			MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Test/TestMesh/Sphere.Sphere'"));
		if (MeshAsset.Succeeded())
		{
			mMesh->SetStaticMesh(MeshAsset.Object);
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial>
			MeshAsset(TEXT("/Script/Engine.Material'/Engine/MapTemplates/Materials/BasicAsset02.BasicAsset02'"));
		if (MeshAsset.Succeeded())
		{
			mMesh->SetMaterial(0, MeshAsset.Object);
		}
	}

	mSphereCollision->SetSphereRadius(50.f);
	mSphereCollision->SetCollisionProfileName(TEXT("PlayerAttack"));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mMovement->InitialSpeed = mSpeed;
	mMovement->ProjectileGravityScale = 0.1f;
	//mMovement->bShouldBounce = true;

	
	SetActorScale3D(FVector(0.3f));
	SetLifeSpan(mDistance / mSpeed);

}

// Called when the game starts or when spawned
void ATestBullet::BeginPlay()
{
	Super::BeginPlay();
	
	mMovement->OnProjectileStop.AddDynamic(this,
		&ATestBullet::ProjectileHit);
}

// Called every frame
void ATestBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestBullet::ProjectileHit(const FHitResult& HitResult)
{
	// UParticleSystem : Cascade Particle System 애셋 타입
	//// FindObject : 참조 있는 애셋을 참조할 때 사용 ( 미리 불러놓은 )
	//UParticleSystem* Particle = FindObject<UParticleSystem>(GetWorld(),
	//		TEXT(""));

	// LoadObject : 참조없는 애셋을 로딩하고 참조할 때 사용
	UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(),
		TEXT("/Script/Engine.ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst'"));


	if (IsValid(Particle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle,
			HitResult.ImpactPoint/*, HitResult.ImpactNormal.Rotation(), true*/);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1,
			1.f, FColor::Blue, TEXT("Particle"));
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1,
			1.f, FColor::Red, TEXT("Particle None"));
	}


	USoundBase* Sound = LoadObject<USoundBase>(GetWorld(),
		TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, HitResult.ImpactPoint);
	}

	// 충돌된 Actor의 TakeDamage 함수를 호출
	FDamageEvent DmgEvent;
	HitResult.GetActor()->TakeDamage(mDamage, DmgEvent, mOwnerController, this);


	Destroy();
}