// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class LABIRINT_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool m = false;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialOff;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialOn;

	UPROPERTY(EditAnywhere, Category = "Components")
	FRotator okretanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacijax;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacijay;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacijaz;

	UPROPERTY(EditAnywhere, Category = "Components")
	float kolikox;

	UPROPERTY(EditAnywhere, Category = "Components")
	float kolikoy;

	UPROPERTY(EditAnywhere, Category = "Components")
	float kolikoz;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UBoxComponent* MyBoxComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
