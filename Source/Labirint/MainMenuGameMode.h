// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LABIRINT_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override; //Override beginplay from the base class

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Play_level1();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Levels_menu();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Control_menu();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Quit_menu();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Back();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel2();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel3();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel4();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel5();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel6();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel7();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel8();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel9();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void OLevel10();

public:
	AMainMenuGameMode();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> MainHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> LevelsHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> OptionHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> VictoryHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UFUNCTION()
	void Provjera();

};
