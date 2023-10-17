// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PitalicaPopravljena.generated.h"

UCLASS()
class LABIRINT_API APitalicaPopravljena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APitalicaPopravljena();

	UFUNCTION(BlueprintCallable, Category = "Pitanja")
	FString GetPitanje();

	UFUNCTION(BlueprintCallable, Category = "Pitanja")
	bool Get_Stanje();

	UFUNCTION(BlueprintCallable, Category = "Pitanja")
	void Back();

	UFUNCTION(BlueprintCallable, Category = "Pitanja")
	void SetOdgovor(FString poruka);

	UFUNCTION(BlueprintCallable, Category = "Pitanja")
	void Provjera();

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialPitalica;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BodyFo;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pitalica", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PitalicaHUDClass;

	UPROPERTY()
	class UUserWidget* PitalicaWidget;

	UPROPERTY(EditAnywhere, Category = "Components")
	FString Pitanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	FString PraviOdgovor;

	UPROPERTY(EditAnywhere, Category = "Components")
	FString Odgovor;

	UPROPERTY(EditAnywhere, Category = "Components")
	bool stanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	int X;

	UPROPERTY(EditAnywhere, Category = "Components")
	int Y;

	UPROPERTY(EditAnywhere, Category = "Components")
	int Z;

	UPROPERTY(EditAnywhere, Category = "goal")
	TSubclassOf<class AGoal> GoalClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	FRotator okretanje;

	UPROPERTY(EditAnywhere, Category = "Components")
	float rotacija;

	UPROPERTY(EditAnywhere, Category = "Components")
	float koliko;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
