// Fill out your copyright notice in the Description page of Project Settings.


#include "Municija.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "MyPawn.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"

// Sets default values
AMunicija::AMunicija()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MaterialMunicija = CreateDefaultSubobject<UMaterial>("MaterialMunicija");

	municija = 10;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	SetRootComponent(MyBoxComponent);
	StaticMesh->SetupAttachment(MyBoxComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMunicija::OnOverlapBegin);

	okretanje = FRotator(0.f, 0.f, 0.f);

	StaticMesh->SetWorldRotation(okretanje);
	koliko = 2.f;
	rotacija = 0;
}

// Called when the game starts or when spawned
void AMunicija::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetMaterial(0, MaterialMunicija);
}

// Called every frame
void AMunicija::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rotacija = rotacija + koliko;
	if (rotacija > 360.f || rotacija < -360)
	{
		rotacija = 0;
	}
	okretanje = FRotator(0.f, rotacija, 0.f);

	StaticMesh->SetWorldRotation(okretanje);
}

void AMunicija::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		Cast<AMyPawn>(OtherActor)->UpdateBr_metaka(municija);
		Cast<AMyPawn>(OtherActor)->Set_Material(MaterialMunicija);
		Destroy();
	}
}

