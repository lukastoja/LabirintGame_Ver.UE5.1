// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LabirintGameState.generated.h"

/**
 * 
 */
UCLASS()
class LABIRINT_API ALabirintGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	ALabirintGameState();

	int32 Points;
};
