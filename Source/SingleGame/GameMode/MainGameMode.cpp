// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../Player/KnightCharacter.h"
#include "../AI/Monster/MonsterDataManager.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = AKnightCharacter::StaticClass();

	MonsterDataManager::GetInst()->Init();
}

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AMainGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* Controller = Super::Login(NewPlayer,
		InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	int32	JobData = 0;

	if (FParse::Value(*Options, TEXT("Job = "), JobData))
	{
		EPlayerJob	Job = (EPlayerJob)JobData;

		switch (Job)
		{
		case EPlayerJob::Knight:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(Sac6, Warning, TEXT("Knight"));
			break;
		case EPlayerJob::Archer:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(Sac6, Warning, TEXT("Archer"));
			break;
		case EPlayerJob::Magicion:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(Sac6, Warning, TEXT("Magicion"));
			break;
		case EPlayerJob::Soldier:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(Sac6, Warning, TEXT("Soldier"));
			break;
		}
	}

	return Controller;
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}