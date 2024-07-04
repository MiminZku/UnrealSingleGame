// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIInfo.h"
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

public:
	UCapsuleComponent* GetCapsule() const { return mCapsule; }

	template <typename T>
	void AddDeathDelegate(T* Object, void(T::* Func)())
	{
		mDeathDelegate.AddUObject(Object, Func);
	}

	virtual void SetState(EAIState State) { mState = State; }
	void SetName(const FString& Name) { mName = Name; }
	
	EAIState GetState() { return mState; }
	const FString& GetName() const { return mName; }


protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	FAIDeathDelegate mDeathDelegate;

	FString mName;

	uint8		mTeamID = 10;

	EAIState	mState = EAIState::Idle;
};
