// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LabirintGameMode.h"
#include "LabirintPlayerController.h"
#include "LabirintCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LabirintGameState.h" 
#include "Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPawn.h"
#include "Blueprint/UserWidget.h"


ALabirintGameMode::ALabirintGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ALabirintPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	PointsToWin = 2;
	poruka = "Dobrodošao";

	bCanRemove = false;

}

void ALabirintGameMode::RemoveDobrodoslicu()
{
	DobrodoslicaWidget->RemoveFromParent();
	GetWorldTimerManager().ClearTimer(RemoveTimerHandle);
}

void ALabirintGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();

	poruka = "Welcome to " + CurrentLevel;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		PC->bShowMouseCursor = false;
	}

	AMyPawn* MyCharacter = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("ovdje sam"));
		}
	}

	if (DobrodoslicaHUDClass != nullptr)
	{
		DobrodoslicaWidget = CreateWidget<UUserWidget>(GetWorld(), DobrodoslicaHUDClass);

		if (DobrodoslicaWidget != nullptr)
		{
			DobrodoslicaWidget->AddToViewport();
		}
	}

	if (CurrentLevel == "Level1" || CurrentLevel == "level2" ||CurrentLevel == "level7")
	{
		PointsToWin = 4;
	}

	if (CurrentLevel == "level3" || CurrentLevel == "level5")
	{
		PointsToWin = 3;
	}

	if (CurrentLevel == "level4" || CurrentLevel == "level8")
	{
		PointsToWin = 5;
	}

	if (CurrentLevel == "level6" || CurrentLevel == "level9")
	{
		PointsToWin = 6;
	}

	GetWorld()->GetTimerManager().SetTimer(RemoveTimerHandle, this, &ALabirintGameMode::RemoveDobrodoslicu, 5.f, false);
}

void ALabirintGameMode::OnGoalHit(bool m)
{
	UE_LOG(LogTemp, Warning, TEXT("\nuspjesno pozvana funkcije"));
	if (ALabirintGameState* GS = Cast<ALabirintGameState>(GameState))
	{
		UE_LOG(LogTemp, Warning, TEXT("\nuspjesno pozvana funkcije123"));
		if (m)
		{
			GS->Points++;
		}
		else
		{
			GS->Points--;
		}
		if (GS->Points >= PointsToWin)
		{
			UWorld* TheWorld = GetWorld();
			FString CurrentLevel = TheWorld->GetMapName();

			if (CurrentLevel == "Level1")
			{
				UGameplayStatics::OpenLevel(this, "level2");
			}
			else if (CurrentLevel == "level2")
			{
				UGameplayStatics::OpenLevel(this, "level3");
			}
			else if (CurrentLevel == "level3")
			{
				UGameplayStatics::OpenLevel(this, "level4");
			}
			else if (CurrentLevel == "level4")
			{
				UGameplayStatics::OpenLevel(this, "level5");
			}
			else if (CurrentLevel == "level5")
			{
				UGameplayStatics::OpenLevel(this, "level6");
			}
			else if (CurrentLevel == "level6")
			{
				UGameplayStatics::OpenLevel(this, "level7");
			}
			else if (CurrentLevel == "level7")
			{
				UGameplayStatics::OpenLevel(this, "level8");
			}
			else if (CurrentLevel == "level8")
			{
				UGameplayStatics::OpenLevel(this, "level9");
			}
			else if (CurrentLevel == "level9")
			{
				UGameplayStatics::OpenLevel(this, "L_Victory");
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("\n%d"), GS->Points);
	}

	
}

FString ALabirintGameMode::Get_Poruka()
{
	return poruka;
}

int ALabirintGameMode::Get_Points()
{
	ALabirintGameState* GS = Cast<ALabirintGameState>(GameState);
	return GS->Points;
}

int ALabirintGameMode::Get_PointsToWin()
{
	return PointsToWin;
}


void ALabirintGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
