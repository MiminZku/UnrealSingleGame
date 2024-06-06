// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject : UObject를 상속받은 클래스를 생성, 생성자에서만 사용 가능
	// FName : 언리얼에서 이름을 붙여줄 떄 사용하는 타입
	// TEXT() : 유니코드 문자열로 만들어주는 매크로
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// mMesh를 root Component로 지정
	SetRootComponent(mMesh);

	// Camera의 부모 Component로 mesh 를 지정
	mCamera->SetupAttachment(mMesh);

	mCamera->SetRelativeLocation(FVector(-300, 0, 150));
	mCamera->SetRelativeRotation(FRotator(-30, 0, 0));

	// 언리얼 에디터에서만 어디에 있는지 표시해줌
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

