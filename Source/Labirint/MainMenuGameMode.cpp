// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "UObject/ConstructorHelpers.h" 
#include "Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPawn.h"
#include "Classes/GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	if (CurrentLevel == "L_MainMenu")
	{
		if (MainHUDClass != nullptr)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);

			if (CurrentWidget != nullptr)
			{
				CurrentWidget->AddToViewport();
				UE_LOG(LogTemp, Warning, TEXT("ovdje sam"));
			}
		}
	}
	else if (CurrentLevel == "L_Victory")
	{
		if (VictoryHUDClass != nullptr)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), VictoryHUDClass);

			if (CurrentWidget != nullptr)
			{
				CurrentWidget->AddToViewport();
				UE_LOG(LogTemp, Warning, TEXT("ovdje sam"));
			}
		}
	}


	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void AMainMenuGameMode::Provjera()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
	}
}

void AMainMenuGameMode::Play_level1()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level1");
}

void AMainMenuGameMode::Levels_menu()
{
	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), LevelsHUDClass);
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void AMainMenuGameMode::Control_menu()
{
	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), OptionHUDClass);
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void AMainMenuGameMode::Quit_menu()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void AMainMenuGameMode::Back()
{
	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	if (CurrentLevel == "L_Victory")
	{
		UGameplayStatics::OpenLevel(this, "L_MainMenu");
	}

	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void AMainMenuGameMode::OLevel2()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level2");
}

void AMainMenuGameMode::OLevel3()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level3");
}

void AMainMenuGameMode::OLevel4()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level4");
}

void AMainMenuGameMode::OLevel5()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level5");
}

void AMainMenuGameMode::OLevel6()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level6");
}

void AMainMenuGameMode::OLevel7()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level7");
}

void AMainMenuGameMode::OLevel8()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level8");
}

void AMainMenuGameMode::OLevel9()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level9");
}

void AMainMenuGameMode::OLevel10()
{
	Provjera();
	UGameplayStatics::OpenLevel(this, "Level10");
}

AMainMenuGameMode::AMainMenuGameMode()
{
}
