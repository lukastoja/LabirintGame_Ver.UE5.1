// Fill out your copyright notice in the Description page of Project Settings.


#include "Zamka2.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "MyPawn.h"

// Sets default values
AZamka2::AZamka2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Zid = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh_Zid");
	Switch = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh_Switch");
	MaterialSwitch = CreateDefaultSubobject<UMaterial>("MaterialSwitch");
	MaterialZid = CreateDefaultSubobject<UMaterial>("MaterialZid");
	

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");

	SetRootComponent(MyBoxComponent);
	Zid->SetupAttachment(MyBoxComponent);
	Switch->SetupAttachment(MyBoxComponent);
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AZamka2::OnOverlapBegin);

	okretanje = FRotator(0.f, 0.f, 0.f);

	Switch->SetWorldRotation(okretanje);
	koliko = 2.f;
	rotacija = 0;
}

// Called when the game starts or when spawned
void AZamka2::BeginPlay()
{
	Super::BeginPlay();
	Switch->SetMaterial(0, MaterialSwitch);
	Zid->SetMaterial(0, MaterialZid);
}

// Called every frame
void AZamka2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rotacija = rotacija + koliko;
	if (rotacija > 360.f || rotacija < -360)
	{
		rotacija = 0;
	}
	okretanje = FRotator(0.f, rotacija, 0.f);

	Switch->SetWorldRotation(okretanje);
}

void AZamka2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		Destroy();
	}
}

