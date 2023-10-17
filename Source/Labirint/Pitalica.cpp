// Fill out your copyright notice in the Description page of Project Settings.


#include "Pitalica.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Goal.h"
#include "MyPawn.h"

// Sets default values
APitalica::APitalica()
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

	X = 0;
	Y = 0;
	Z = 0;

	//stanje = false;

	//Box->OnComponentBeginOverlap.AddDynamic(this, &APitalica::OnOverlapBegin);
	Box->OnComponentBeginOverlap.AddDynamic(this, &APitalica::OnOverlapBegin);
}

void APitalica::Back()
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
		}
	}
	MyPlayer->SetPause(false);
}

FString APitalica::GetPitanje()
{
	return Pitanje;
}

/*bool APitalica::Get_Stanje()
{
	return stanje;
}*/

FString APitalica::GetOdgovor()
{
	return Odgovor;
}


void APitalica::SetOdgovro(FString poruka)
{
	Odgovor = poruka;
}

void APitalica::Provjera()
{
	if (PraviOdgovor.Equals(Odgovor))
	{
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
	}
}

// Called when the game starts or when spawned
void APitalica::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APitalica::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APitalica::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ne radi"));
}

/*void APitalica::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ne radi"));
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Radi do davde!!!!!!!!!!"));
		//stanje = true;

		UE_LOG(LogTemp, Warning, TEXT("Overlap je zapoceo"));
		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		APlayerController* PC = GetWorld()->GetFirstPlayerController();

		if (MyPlayer != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Radi do davde!"));
			if (PitalicaHUDClass != nullptr)
			{
				PitalicaWidget = CreateWidget<UUserWidget>(GetWorld(), PitalicaHUDClass);
				PitalicaWidget->AddToViewport();
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug dssd!"));
			}

			if (PC)
			{
				PC->bShowMouseCursor = true;
				PC->bEnableClickEvents = true;
				PC->bEnableMouseOverEvents = true;
			}
		}
		MyPlayer->SetPause(true);
	}
}*/

