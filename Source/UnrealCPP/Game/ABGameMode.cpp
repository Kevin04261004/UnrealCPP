// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Player/ABPlayerController.h"

AABGameMode::AABGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class != nullptr)
	//{
	//	DefaultPawnClass = ThirdPersonClassRef.Class;
	//}

	// static ConstructorHelpers::FClassFinder<APawn> BlueprintTestPawnClassRef(TEXT("/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C"));
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class != nullptr)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}


	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/UnrealCPP.ABPlayerController"));
	if (PlayerControllerClassRef.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	ClearScore = 3;
	CurrentScore = 0;
	bIsCleared = false;
}

void AABGameMode::OnPlayerScoreChanged(int32 NewPlayerScore)
{
	CurrentScore = NewPlayerScore;

	AABPlayerController* ABPlayerController = Cast<AABPlayerController>(GetWorld()->GetFirstLocalPlayerFromController());
	if (ABPlayerController != nullptr)
	{
		ABPlayerController->GameScoreChanged(CurrentScore);
	}
	
	if (CurrentScore >= ClearScore)
	{
		bIsCleared = true;

		if (ABPlayerController != nullptr)
		{
			ABPlayerController->GameClear();
		}
	}
}

void AABGameMode::OnPlayerDead()
{
	AABPlayerController* ABPlayerController = Cast<AABPlayerController>(GetWorld()->GetFirstLocalPlayerFromController());
	if (ABPlayerController != nullptr)
	{
		ABPlayerController->GameOver();
	}
}

bool AABGameMode::IsGameCleared()
{
	return bIsCleared;
}
