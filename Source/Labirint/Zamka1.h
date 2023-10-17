// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zamka1.generated.h"

UCLASS()
class LABIRINT_API AZamka1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZamka1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UParticleSystemComponent* Particles;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UAudioComponent* Audio;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* MyBoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	FVector MoveDirection;

	UPROPERTY(EditAnywhere, Category = "Components")
	float MoveScale;

	UPROPERTY(EditAnywhere, Category = "Components")
	float x;

	UPROPERTY(EditAnywhere, Category = "Components")
	float y;

	UPROPERTY(EditAnywhere, Category = "Components")
	float z;

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialMovable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
