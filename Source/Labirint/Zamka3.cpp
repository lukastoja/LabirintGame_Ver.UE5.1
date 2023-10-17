// Fill out your copyright notice in the Description page of Project Settings.


#include "Zamka3.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Bullet.h"

// Sets default values
AZamka3::AZamka3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Zid = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh_Zid");
	MaterialZid = CreateDefaultSubobject<UMaterial>("MaterialZid");

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");

	SetRootComponent(MyBoxComponent);
	Zid->SetupAttachment(MyBoxComponent);
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AZamka3::OnOverlapBegin);

	HP = 1;
}

// Called when the game starts or when spawned
void AZamka3::BeginPlay()
{
	Super::BeginPlay();
	Zid->SetMaterial(0, MaterialZid);
}

// Called every frame
void AZamka3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZamka3::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ABullet>(OtherActor) != nullptr)
	{
		HP--;
		OtherActor->Destroy();
	}
	if (HP <= 0)
	{
		Destroy();
	}
}

