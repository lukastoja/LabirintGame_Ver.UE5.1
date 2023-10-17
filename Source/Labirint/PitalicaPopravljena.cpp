// Fill out your copyright notice in the Description page of Project Settings.


#include "PitalicaPopravljena.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyPawn.h"
#include "Goal.h"

// Sets default values
APitalicaPopravljena::APitalicaPopravljena()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Body = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	BodyFo = CreateDefaultSubobject<UStaticMeshComponent>("BodyFoComoponent");
	MaterialPitalica = CreateDefaultSubobject<UMaterial>("MaterialPitalica");

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Body->SetupAttachment(Box);
	BodyFo->SetupAttachment(Box);

	Box->OnComponentBeginOverlap.AddDynamic(this, &APitalicaPopravljena::OnOverlapBegin);
	stanje = false;

	okretanje = FRotator(0.f, 0.f, 0.f);

	Body->SetWorldRotation(okretanje);
	BodyFo->SetWorldRotation(okretanje);
	koliko = 2.f;
	rotacija = 0;
}

FString APitalicaPopravljena::GetPitanje()
{
	return Pitanje;
}

bool APitalicaPopravljena::Get_Stanje()
{
	return stanje;
}

void APitalicaPopravljena::Back()
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (MyPlayer != NULL)
	{

		if (PitalicaWidget != nullptr)
		{
			PitalicaWidget->RemoveFromParent();
		}

		if (PC)
		{
			PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
		}
	}
	MyPlayer->SetPause(false);
}

void APitalicaPopravljena::SetOdgovor(FString poruka)
{
	Odgovor = poruka;
}

void APitalicaPopravljena::Provjera()
{
	if (PraviOdgovor.Equals(Odgovor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tocan odgovor"));
		if (GoalClass)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParameters.bNoFail = true;
			SpawnParameters.Owner = this;

			FTransform GoalSpawnTransform;
			GoalSpawnTransform.SetLocation(FVector(X, Y, Z));
			GoalSpawnTransform.SetRotation(GetActorRotation().Quaternion());
			GoalSpawnTransform.SetScale3D(FVector(1.f));

			GetWorld()->SpawnActor<AGoal>(GoalClass, GoalSpawnTransform, SpawnParameters);
		}

		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		if (MyPlayer != NULL)
		{

			if (PitalicaWidget != nullptr)
			{
				PitalicaWidget->RemoveFromParent();
			}

			if (PC)
			{
				PC->bShowMouseCursor = false;
				PC->bEnableClickEvents = false;
				PC->bEnableMouseOverEvents = false;
			}
		}
		MyPlayer->SetPause(false);
		Destroy();
	}
}

// Called when the game starts or when spawned
void APitalicaPopravljena::BeginPlay()
{
	Super::BeginPlay();
	Body->SetMaterial(0, MaterialPitalica);
	BodyFo->SetMaterial(0, MaterialPitalica);
}

// Called every frame
void APitalicaPopravljena::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rotacija = rotacija + koliko;
	if (rotacija > 360.f || rotacija < -360)
	{
		rotacija = 0;
	}
	okretanje = FRotator(0.f, rotacija, 0.f);

	Body->SetWorldRotation(okretanje);
	BodyFo->SetWorldRotation(okretanje);
}

void APitalicaPopravljena::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ne radi"));
	stanje = true;
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		if (PitalicaHUDClass != nullptr)
		{
			PitalicaWidget = CreateWidget<UUserWidget>(GetWorld(), PitalicaHUDClass);
			PitalicaWidget->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug dssd!"));
		}

		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		if (MyPlayer != NULL)
		{
			if (PC)
			{
				PC->bShowMouseCursor = true;
				PC->bEnableClickEvents = true;
				PC->bEnableMouseOverEvents = true;
			}
		}
		MyPlayer->SetPause(true);
	}
}

