// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "LabirintGameMode.h"
#include "MyPawn.h"
#include "Bullet.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComoponent");
	RootComponent = StaticMesh;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	MyBoxComponent->SetupAttachment(RootComponent);

	MaterialOff = CreateDefaultSubobject<UMaterial>("MaterialOff");
	MaterialOn = CreateDefaultSubobject<UMaterial>("MaterialOn");

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);

	okretanje = FRotator(0.f, 0.f, 0.f);

	StaticMesh->SetWorldRotation(okretanje);
	kolikox = 2.f;
	kolikoy = 2.f;
	kolikoz = 2.f;
	rotacijax = 0;
	rotacijay = 0;
	rotacijaz = 0;
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(100, 100, 100), FColor::White, true, -1, 0, 10);

	StaticMesh->SetMaterial(0, MaterialOff);
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rotacijax = rotacijax + kolikox;
	rotacijay = rotacijay + kolikoy;
	rotacijaz = rotacijaz + kolikoz;
	if (rotacijax > 360.f || rotacijax < -360)
	{
		rotacijax = 0;
	}
	if (rotacijay > 360.f || rotacijay < -360)
	{
		rotacijay = 0;
	}
	if (rotacijaz > 360.f || rotacijaz < -360)
	{
		rotacijaz = 0;
	}
	okretanje = FRotator(rotacijay, rotacijaz, rotacijax);

	StaticMesh->SetWorldRotation(okretanje);
}

void AGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<UStaticMeshComponent>(OverlappedComp) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Treba dodati return"));
	}
	if (((Cast<AMyPawn>(OtherActor) != nullptr) || (Cast<ABullet>(OtherActor) != nullptr)) && Cast<UBoxComponent>(OverlappedComp) != nullptr)
	{
		if (m == false)
		{
			m = true;
			StaticMesh->SetMaterial(0, MaterialOn);
		}
		else 
		{
			m = false;
			StaticMesh->SetMaterial(0, MaterialOff);
		}
		if (ALabirintGameMode* GM = Cast<ALabirintGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GM->OnGoalHit(m);
		}
	}
}

