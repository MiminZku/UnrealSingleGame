// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Camera/CameraComponent.h>	// 순환 참조 일어날 일이 없어서 괜찮음
#include "../GameInfo.h"
#include "CoreMinimal.h"
//#include "EngineMinimal.h";
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SINGLEGAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// UObject 클래스에서 사용 가능, 에디터와 연결되는 등 특수한 옵션 설정 해줄 때 사용
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties?application_version=5.3
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
	// 스마트 포인터 (레퍼런스 카운트)
	//TObjectPtr<UStaticMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// 입력 키에 따른 호출될 함수를 등록
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
