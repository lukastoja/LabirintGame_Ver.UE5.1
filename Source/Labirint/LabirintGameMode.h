// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LabirintGameMode.generated.h"

UCLASS(minimalapi)
class ALabirintGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override; //Override beginplay from the base class

public:
	ALabirintGameMode();

	void OnGoalHit(bool m);

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	int32 PointsToWin;

	UPROPERTY(EditAnywhere, Category = "Dobrodoslica")
	FString poruka;

	UFUNCTION(BlueprintPure, Category = "Dobrodoslica")
	FString Get_Poruka();

	UPROPERTY(EditAnywhere, Category = "Dobrodoslica")
	FString Poruka_provjera;

	UFUNCTION(BlueprintPure, Category = "Dobrodoslica")
	int Get_Points();

	UFUNCTION(BlueprintPure, Category = "Dobrodoslica")
	int Get_PointsToWin();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Br_metaka", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dobrodoslica", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> DobrodoslicaHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dobrodoslica", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> ProvjeraHUDClass;


	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY()
	class UUserWidget* DobrodoslicaWidget;

	UPROPERTY()
	class UUserWidget* ProvjeraWidget;

	/*za Timer opcije*/
	bool bCanRemove;

	FTimerHandle RemoveTimerHandle;

	void RemoveDobrodoslicu();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};