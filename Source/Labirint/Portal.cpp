// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "MyPawn.h"
#include "Blueprint/UserWidget.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	MaterialPortal = CreateDefaultSubobject<UMaterial>("MaterialPortal");
	MyBoxComponent->SetupAttachment(RootComponent);
	StaticMesh->SetupAttachment(MyBoxComponent);

	x = -740.f;
	y = 280.f;
	z = 250.f;

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);

	StaticMesh->SetWorldRotation(okretanje);
	koliko = 2.f;
	rotacija = 0;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetMaterial(0, MaterialPortal);
}

// Called every frame
void APortal::Tick(float DeltaTime)
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

void APortal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(Cast<AMyPawn>(OtherActor) != nullptr)
	{
		Cast<AMyPawn>(OtherActor)->X = x;
		Cast<AMyPawn>(OtherActor)->Y = y;
		Cast<AMyPawn>(OtherActor)->Z = z;
		Cast<AMyPawn>(OtherActor)->TP = true;
		Cast<AMyPawn>(OtherActor)->PortalWidget->AddToViewport();
	}
}


