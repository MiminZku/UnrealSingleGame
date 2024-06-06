// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject : UObject�� ��ӹ��� Ŭ������ ����, �����ڿ����� ��� ����
	// FName : �𸮾󿡼� �̸��� �ٿ��� �� ����ϴ� Ÿ��
	// TEXT() : �����ڵ� ���ڿ��� ������ִ� ��ũ��
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// mMesh�� root Component�� ����
	SetRootComponent(mMesh);

	// Camera�� �θ� Component�� mesh �� ����
	mCamera->SetupAttachment(mMesh);

	mCamera->SetRelativeLocation(FVector(-300, 0, 150));
	mCamera->SetRelativeRotation(FRotator(-30, 0, 0));

	// �𸮾� �����Ϳ����� ��� �ִ��� ǥ������
#if WITH_EDITORONLY_DATA
	mMesh->bVisualizeComponent = true;
#endif
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

