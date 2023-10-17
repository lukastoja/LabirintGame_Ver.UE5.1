// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zamka2.generated.h"

UCLASS()
class LABIRINT_API AZamka2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZamka2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Zid;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Switch;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* MyBoxComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	FRotator okretanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacija;

	UPROPERTY(EditAnywhere, Category = "Components")
	float koliko;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialSwitch;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialZid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
