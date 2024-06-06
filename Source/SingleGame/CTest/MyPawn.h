// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Camera/CameraComponent.h>	// ��ȯ ���� �Ͼ ���� ��� ������
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
	// UObject Ŭ�������� ��� ����, �����Ϳ� ����Ǵ� �� Ư���� �ɼ� ���� ���� �� ���
	// https://dev.epicgames.com/documentation/ko-kr/unreal-engine/unreal-engine-uproperties?application_version=5.3
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
	// ����Ʈ ������ (���۷��� ī��Ʈ)
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
	// �Է� Ű�� ���� ȣ��� �Լ��� ���
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
