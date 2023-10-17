// Fill out your copyright notice in the Description page of Project Settings.


#include "Zamka1.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Bullet.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Components/AudioComponent.h"
#include "MyPawn.h"

// Sets default values
AZamka1::AZamka1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Particles = CreateDefaultSubobject<UParticleSystemComponent>("Particles");
	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	MaterialMovable = CreateDefaultSubobject<UMaterial>("MaterialMovable");

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	
	SetRootComponent(MyBoxComponent);
	StaticMesh->SetupAttachment(MyBoxComponent);
	Particles->SetupAttachment(MyBoxComponent);
	Audio->SetupAttachment(Particles);
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AZamka1::OnOverlapBegin);
	MoveScale = 200.f;
}

// Called when the game starts or when spawned
void AZamka1::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetMaterial(0, MaterialMovable);
	MoveDirection = FVector(x, y, z);
	
}

// Called every frame
void AZamka1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveDelta = (MoveDirection * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(GetWorld()->GetTimeSeconds()))) * MoveScale;
	AddActorWorldOffset(MoveDelta, true);
}

void AZamka1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ABullet>(OtherActor) != nullptr)
	{
		return;
	}
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("RestartLevel");
	}
}