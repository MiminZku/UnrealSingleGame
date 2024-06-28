// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

DECLARE_MULTICAST_DELEGATE(FAIDeathDelegate);

UCLASS()
class SINGLEGAME_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCapsuleComponent* GetCapsule() const { return mCapsule; }

	template <typename T>
	void AddDeathDelegate(T* Object, void(T::* Func)())
	{
		mDeathDelegate.AddUObject(Object, Func);
	}


protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	FAIDeathDelegate mDeathDelegate;
};
